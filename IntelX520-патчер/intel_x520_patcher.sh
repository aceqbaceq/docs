#!/usr/bin/env bash
#
# Simple Intel x520 EEPROM patcher
# Modifies the EEPROM to unlock the card for non-intel branded SFP modules.
#
# Copyright 2024 Ivan Vatlin <me@jeffangelion.ru>
#
# Licensed under the GPLv3
#
# Based on research described at https://forums.servethehome.com/index.php?threads/patching-intel-x520-eeprom-to-unlock-all-sfp-transceivers.24634/
#
# Quick explanation of what's going on:
# Looking at the Intel driver at e.g. https://elixir.bootlin.com/linux/v5.8/source/drivers/net/ethernet/intel/ixgbe/ixgbe_type.h#L2140 we can see
# that the bit 0x1 at Address 0x58 contains a configuration setting whether the card allows any SFP modules or if Intel specific ones are enforced
# by the driver.
#
# Addr Bitstring
# 0x58 xxxxxxx0 means Intel specific SFPs
# 0x58 xxxxxxx1 means any SFP is allowed.
#
# Using the parameter allow_unsupported_sfp for the kernel module we can tell the driver to accept any SFPs.
# But this tool will flip the right bit 1 to make that change permanent in the configuration bits in the EEPROM,
# thus making kernel module parameters unnecessary.
#
# export YOLO=1 for auto usage if you are brave enough
yolo=${YOLO:-0}

intel="0x8086"

declare -A x520_card_ids=( ["0x10fb"]="82599ES 10-Gigabit SFI/SFP+ Network Connection" ["0x154d"]="Ethernet 10G 2P X520 Adapter" )
# declare -A x710_card_ids=( ["0x1572"]="Ethernet Controller X710 for 10GbE SFP+" )

function verify_interface {
    local interface=$1
    local vendor_id="$(cat /sys/class/net/$interface/device/vendor)"
    local device_id="$(cat /sys/class/net/$interface/device/device)"
    if [[ -z $vendor_id || -z $device_id ]]; then
        printf "%s: can't read interface data, skipping...\n" "$interface"
        return
    fi
    if [[ $vendor_id == "$intel" ]]; then
        printf "%s: recognized an Intel manufactured card\n" "$interface"
    else
        printf "%s: not an Intel manufactured card, skipping...\n" "$interface"
        return
    fi
    if [[ "${!x520_card_ids[*]}" =~ $device_id ]]; then
        printf "%s: recognized the %s card\n" "$interface" "${x520_card_ids[$device_id]}"
        unlock_x520 "$interface" "$vendor_id" "$device_id"
    # elif [[ "${!x710_card_ids[*]}" =~ $device_id ]]; then
    #    printf "%s: recognized the %s card\n" "$interface" "${x710_card_ids[$device_id]}"
    #    unlock_x710 $interface
    else
        printf "%s: not a supported card, skipping...\n" "$interface"
        return
    fi
    return
}

function unlock_x520 {
    local interface=$1
    local vendor_id=$2
    local device_id=$3
    local magic="${device_id}${vendor_id:2}"
    # get current bit
    local current_eeprom_value_hex="$(ethtool -e $interface offset 0x58 length 1 raw on | hexdump -e '"%2x"')"
    local current_eeprom_value="$((16#$current_eeprom_value_hex))"
    if [[ -z $current_eeprom_value_hex ]]; then
        printf "%s: failed to get EEPROM value, is ethtool installed?\n" "$interface"
        return
    elif (( ($current_eeprom_value & 0x1) == 0x1 )); then
        printf "%s: card is already unlocked, skipping...\n" "$interface"
        return
    else
        local new_eeprom_value=$((current_eeprom_value | 1))
        local new_eeprom_value_hex=$( (printf '%x' $new_eeprom_value) )
        local unlock_cmd=("ethtool" "-E" "${interface}" "magic" "${magic}" "offset" "0x58" "value" "0x${new_eeprom_value_hex}" "length" "1")
        if [[ $yolo -eq 0 ]]; then
            printf "%s: about to run %s\n" "$interface" "${unlock_cmd[*]}"
            printf "%s: this operation will write data to your ethernet card eeprom. Type 'yes' to confirm: \n" "$interface"
            read -r answer
            if [[ ${answer,,} != "yes" ]]; then
                printf "%s: operation aborted, skipping...\n" "$interface"
                return
            else
                "${unlock_cmd[@]}"
            fi
        else
            printf "%s: running %s" "$interface" "${unlock_cmd[*]}"
            "${unlock_cmd[@]}"
        fi
    fi
    # check if bit is actually set
    if [[ "$(ethtool -e $interface offset 0x58 length 1 raw on | hexdump -e '"%2x"')" == $new_eeprom_value_hex ]]; then
        printf "%s: successfully unlocked, reboot for changes to take effect\n" "$interface"
    fi
}

# function unlock_x710 {}

if [[ -z $1 ]]; then
        printf "%s <interfaces>\n" "$0"
        exit 255
fi

while [[ $# -gt 0 ]]; do
    verify_interface "$1"
    shift
done