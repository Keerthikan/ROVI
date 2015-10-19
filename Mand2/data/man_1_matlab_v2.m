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
hold all;
x = [0.7 1 1.1 1.35 1.6 2  3 4 5 6];
[ax h1 h2] = plotyy(ext_var, path_length_ave, ext_var, time_ave);
plot(ext_var, analyse_time_ave,'b');

set(gca,'XTick',x);
set(gca,'XTickLabel',x);
%axis([0 6.5 0 120])

rectangle('Position', [0.7, -2, 1.3, 190], 'LineStyle', '--', 'EdgeColor', 'r');
rectangle('Position', [1.1, -2, 0.5, 190], 'LineStyle', '--', 'EdgeColor', 'b');
rectangle('Position', [1.35, -2, 6, 190], 'LineStyle', '--', 'EdgeColor', 'g');

xlabel('Epsilon variable');
axes(ax(1)); ylabel('Length in Rad                             Movement time in sec');
%axis([0 6.5 0 120])

axes(ax(2)); ylabel('Planning time in sec');
%axis([0 6.5 0 inf])

legend('Planning time','Path length', 'Movement time');
title('Estimation of epsilon')

figure(2)
plot(ext_var, path_length_ave);
