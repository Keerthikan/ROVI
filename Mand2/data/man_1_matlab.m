clc;clear;close all;
ext_1 = csvread('ext1.csv');
ext_2 = csvread('ext2.csv');
ext_3 = csvread('ext3.csv');
ext_4 = csvread('ext4.csv');
ext_5 = csvread('ext5.csv');
ext_6 = csvread('ext6.csv');
ext_7 = csvread('ext7.csv');
ext_8 = csvread('ext8.csv');
ext_9 = csvread('ext9.csv');
ext_0 = csvread('ext0.csv');

ext_var = ext_1(:,1);

path_size = [ext_1(:,2) ext_2(:,2) ext_3(:,2) ext_4(:,2) ext_5(:,2) ext_6(:,2) ext_7(:,2) ext_8(:,2) ext_9(:,2) ext_0(:,2)];
time = [ext_1(:,3) ext_2(:,3) ext_3(:,3) ext_4(:,3) ext_5(:,3) ext_6(:,3) ext_7(:,3) ext_8(:,3) ext_9(:,3) ext_0(:,3)];

path_length = [ext_1(:,4) ext_2(:,4) ext_3(:,4) ext_4(:,4) ext_5(:,4) ext_6(:,4) ext_7(:,4) ext_8(:,4) ext_9(:,4) ext_0(:,4)];
analyse_time = [ext_1(:,5) ext_2(:,5) ext_3(:,5) ext_4(:,5) ext_5(:,5) ext_6(:,5) ext_7(:,5) ext_8(:,5) ext_9(:,5) ext_0(:,5)];


path_size_ave = mean(path_size.')';
time_ave = mean(time.')';

analyse_time_ave = mean(analyse_time.')';
path_length_ave = mean(path_length.')';

figure(1)
x = [0.8 1 1.2 1.35 1.5 1.9 2  3 4 5 6];
[ax h1 h2] = plotyy(ext_var, path_size_ave, ext_var, time_ave);
set(gca,'XTick',x);
set(gca,'XTickLabel',x);
axis([0 6.5 0 120])

rectangle('Position', [0.8, -2, 1.1, 190], 'LineStyle', '--', 'EdgeColor', 'r');
rectangle('Position', [1.2, -2, 0.3, 190], 'LineStyle', '--', 'EdgeColor', 'b');
rectangle('Position', [1.35, -2, 6, 190], 'LineStyle', '--', 'EdgeColor', 'g');

xlabel('Epsilon variable');
axes(ax(1)); ylabel('Path size in N');
axis([0 6.5 0 120])

axes(ax(2)); ylabel('Planning time in sec','Color','r');
axis([0 6.5 0 inf])

legend('Analyse time', 'Path length');
title('Estimation of epsilon')

figure(2)
[ax h3 h4] = plotyy(ext_var, path_length_ave, ext_var, analyse_time_ave);

%rectangle('Position', [0.8, -2, 1.1, 20], 'LineStyle', '--', 'EdgeColor', 'r');
%rectangle('Position', [1.2, -2, 0.3, 20], 'LineStyle', '--', 'EdgeColor', 'b');
%rectangle('Position', [1.35, -2, 6, 20], 'LineStyle', '--', 'EdgeColor', 'g');

xlabel('Epsilon variable');
axes(ax(1)); ylabel('Path length');
axis([0 6.5 5 11])

axes(ax(2)); ylabel('Analyse time in sec');
axis([0 6.5 9 18])

legend('Planning time', 'Path length');
title('Estimation of epsilon')