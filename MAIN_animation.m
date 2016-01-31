% MAIN.m  --  Animation of the Driven Damped Pendulum Fractal
%
%
clc; clear;
flagSaveAnimation = false;

% Specify the initial search grid
q = linspace(-pi,pi,150);  %Angles
w = linspace(-5,5,80);  %Rates

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
tSpan = [0, 2*pi*15];
nData = ceil((tSpan(2)-tSpan(1))/dt);
t = linspace(tSpan(1), tSpan(2),nData);
Z = rk4(dynSys,t,Z0);

if flagSaveAnimation
% Set up stuff for writing animation to file:
vidObj = VideoWriter('DrivenDampedPendulum.mp4','MPEG-4');   %#ok<*UNRCH> %This doesn't work on Linux   :-(   windows only
vidObj.Quality = 100;
open(vidObj);
end

% Plot a few of the frames:
hFig = figure(1); clf; hFig.Color = 0.1*[1,1,1];
axis([-4*pi,4*pi,-3,3]); axis off;
idxPlot = 1:1:nData;
dotSize = 15*ones(size(E0));
dotColor = sqrt(E0-min(E0));  %Scale to make nice colors
for i=idxPlot
    qPlot = Z(1,:,i);
    wPlot = Z(2,:,i);
    if i==1
        hDots = scatter(qPlot,wPlot,dotSize,dotColor,'.');
    else
        set(hDots,'XData',qPlot,'YData',wPlot);
    end
    axis([-3*pi,3*pi,-3,3]); axis off;
    set(gca,'Clipping','off');
    drawnow;
    
    if flagSaveAnimation
    % Save the frame:
    writeVideo(vidObj,getframe(hFig));
    end
end

if flagSaveAnimation
close(vidObj);
end









