% MAIN.m  --  Animation of the Driven Damped Pendulum Fractal 
%
%
clc; clear;

% Specify the initial search grid
q = linspace(-pi,pi,250);  %Angles
w = linspace(-5,5,180);  %Rates

% Expand out to a grid:
[qq, ww] = meshgrid(q,w);
Q0 = reshape(qq,1,numel(qq));
W0 = reshape(ww,1,numel(ww));
Z0 = [Q0;W0];
E0 = 2*cos(Q0) + W0.^2;  %Initial energy

% Dynamical system - driven damped pendulum
dynSys = @(t,z)( [z(2,:);  cos(t) - 0.1*z(2,:) - sin(z(1,:))] );

% Numerical integration of system:
dt = 0.02;
tSpan = [0, 50];
nData = ceil((tSpan(2)-tSpan(1))/dt);
t = linspace(tSpan(1), tSpan(2),nData);
Z = rk4(dynSys,t,Z0);

% Plot a few of the frames:
hFig = figure(1); clf; hFig.Color = 0.1*[1,1,1];
idxPlot = 1:2:nData;
dotSize = 6*ones(size(E0));
dotColor = sqrt(E0-min(E0));  %Scale to make nice colors
for i=idxPlot
    qPlot = Z(1,:,i);
    wPlot = Z(2,:,i);
    scatter(qPlot,wPlot,dotSize,dotColor,'.');
    axis([-3*pi,3*pi,-3,3]); axis off;
    pause(0.04);
end










