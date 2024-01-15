function y = f(x)
    y = x .^ 2;
endfunction;

X=[-4096:4095]/64;
Y = f(X);
# plot(X, Y);

F = fft(Y);
S = [0:2047]/2048;
