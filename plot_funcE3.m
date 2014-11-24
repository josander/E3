% plot

clc
clf
clear all

% energies
% load the data file
distData = importdata('distribution.data');
set(gcf,'renderer','painters','PaperPosition',[0 0 12 6]);
Size = size(distData);

%plot
figure(1);
subplot(2,2,1)
hist(distData(1:10,1));


%plot
subplot(2,2,2)
hist(distData(1:100,2));

%plot
subplot(2,2,3)
hist(distData(1:1000,3));

%plot
subplot(2,2,4)
hist(distData(1:10000,4));

%% Task 4

data = importdata('MC.txt');

c = xcorr(data);

plot(c);
