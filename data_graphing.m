% reading data
T = readmatrix('time_data.txt');
data = readmatrix('distance_data');

% graphing
plot(T, data); grid;
title('Title');
xlabel('time [ms]');
ylabel('distance [cm]');