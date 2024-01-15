Fs = 12/60
alpha = (1-e^(-5/60))

b = [alpha];
a = [1 -(1-alpha)];

[H, W] = freqz(b, a, 1024, Fs);

f3db = Fs/(2*pi)*acos(1-(alpha^2)/(2*(1-alpha)))

plot(W, 20*log10(abs(H)), [f3db, f3db], [-40, 0]);
grid on
