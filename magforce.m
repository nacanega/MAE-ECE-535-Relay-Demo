% Nolan Canegallo
% MAE/ECE 535 Demo Project
% Due 26 June 2023
clear; clc; close all;
%% Magnetic force as function of gap
data = [
    0.01, -.264001;
    0.02, -.191758;
    0.03, -.150108;
    0.04, -.121877;
    0.05, -.101318;
    0.06, -.0866876;
    0.07, -.074813;
    0.08, -.0648187;
    0.09, -.0573948;
    0.10, -.04565;
]; % in   % N
   % gap  % Mag. Force

% Polynomial Fit and evaluation
F_mag = polyfit(data(:,1)*25.4,data(:,2),4);
x = 25.4*(0:0.01:0.1);
yth = polyval(F_mag,x);

% Plot fit and data on same figure
f1 = figure(1);
plot(x,abs(yth),'-r')
hold on
plot(data(:,1)*25.4,abs(data(:,2)),'ok')
hold off
xlabel('Gap Distance, mm')
ylabel('Force Magnitude, N')
legend(["Quartic Fit","FEMM Simulation"],"Location","ne")
grid on
axis tight

%% Calculate angular behavior
th0 = 0;        % Initial angle rad
w0 = 0;         % Initial anglular velocity rad/s
g = 9.81;       % m/s^2


y0 = 0.1*25.4e-3;   % Initial gap m
s0 = 3.85e-3;       % Initial spring compression m
r_mag = 94e-3;       % Magnet force arm m
r_cm = 58e-3;        % Center of mass arm m
r_spr = 15e-3;       % Spring force arm
ks = 316.65;        % Spring constant N/m
m = 32e-3;          % Mass kg
I = m*r_cm^2;        %

t0 = 0;     % start time
tf = 0.5;   % stop time
dt = 1e-5;  % time step

times = t0:dt:tf;   % Precalculate time vector

yth = @(th) y0+r_mag*th;                                % y as f(theta)
stretch = @(th) r_spr*th - s0;                          % stretch as f(theta)
tauspr = @(th) (r_spr) * (-stretch(th)*ks);             % spring torque as f(theta) [small angle]
taug = @(th) (r_cm) * (-m*g);                           % gravity torque as f(theta) [small angle]
taumag = @(th) (r_mag) * polyval(F_mag,yth(th));        % magnetic torque as f(theta) [small angle]

% yth = @(th) y0+lmag*sin(th);                                % y as f(theta)
% stretch = @(th) lspr*sin(th) - s0;                          % stretch as f(theta)
% tauspr = @(th) (lspr*cos(th)) * (-stretch(th)*ks);          % spring torque as f(theta) [assumes force vertical only]
% taug = @(th) (lcm*cos(th)) * (-m*g);                        % gravity torque as f(theta) [assumes force vertical only]
% taumag = @(th) (lmag*cos(th)) * polyval(F_mag,yth(th));     % magnetic torque as f(theta) [assumes force vertical only]

%% Simulation with magnet on, Arm starts at NC

th = th0;                                    % set current angle
w = w0;                                      % set current angular velocity
a0 = (tauspr(th) + taug(th) + taumag(th))/I; % set initial angular acceleration rad/s^2
a = a0;                                      % set current angular acceleration

results = zeros(length(times),5);            % preallocate results
results(1,:) = [t0,th0,w0,a0,y0];            % set initial row

for i = 2:length(times) % iterate for rest of the rows
    y = yth(th);    % calculate gap
    dth = w;        % set dtheta/dt
    dw = a;         % set domega/dt

    tau = tauspr(th) + taug(th) + taumag(th); % calculate torque
    a = tau/I;                                % update ang. accel
    th = th + dth*dt;                         % update ang. vel
    w = w + dw*dt;                            % update ang. pos
    results(i,:) = [times(i),th,w,a,y];       % save to results

    if y < 0                                  % check if zero gap reached
        if i < length(times)                  % if still empty entries
            results(i+1:end,:) = [];          % delete empty entries
        end
        break;                                % exit loop early
    end
end

% Plot angle vs time
f2 = figure;
plot(results(:,1),results(:,2))
xlabel('Time, s')
ylabel('Angle, rad')
grid on
axis tight

% Plot ang. vel vs time
f3 = figure;
plot(results(:,1),results(:,3))
xlabel('Time, s')
ylabel('Anglular Velocity, rad/s')
grid on
axis tight

% Plot ang. acccel vs time
f4 = figure;
plot(results(:,1),results(:,4))
xlabel('Time, s')
ylabel('Angular Acceleration, rad/s^2')
grid on
axis tight

% Plot gap vs time
f5 = figure;
plot(results(:,1),results(:,5)*1000)
grid on
axis tight
xlabel('Time, s')
ylabel('Gap Distance, mm')

%% Simulation with magnet off, Arm starts at NO

th = results(end,2);                     % set current angle
w = 0;                                   % set current angular velocity
a0 = (tauspr(th) + taug(th))/I;          % set initial angular acceleration rad/s^2
a = a0;                                  % set current angular acceleration 

results2 = zeros(length(times),5);       % preallocate results
results2(1,:) = [t0, th, w, a, yth(th)]; % set initial row

for i = 2:length(times) % iterate for rest of the rows
    y = yth(th);    % calculate gap
    dth = w;        % set dtheta/dt
    dw = a;         % set domega/dt
    
    tau = tauspr(th) + taug(th);    % calculate torque
    a = tau/I;                      % update ang. accel
    th = th + dth*dt;               % update ang. vel
    w = w + dw*dt;                  % update ang. pos
    results2(i,:) = [times(i),th,w,a,y];    % save to results

    if y > y0                           % check if max gap reached
        if i < length(times)            % if still empty entries
            results2(i+1:end,:) = [];   % delete empty entries
        end
        break;                          % exit loop early
    end
end

% Plot angle vs time
f6 = figure;
plot(results2(:,1),results2(:,2))
xlabel('Time, s')
ylabel('Angle, rad')
grid on
axis tight

% Plot ang. vel vs time
f7 = figure;
plot(results2(:,1),results2(:,3))
xlabel('Time, s')
ylabel('Anglular Velocity, rad/s')
grid on
axis tight

% Plot ang. accel vs time
f8 = figure;
plot(results2(:,1),results2(:,4))
xlabel('Time, s')
ylabel('Angular Acceleration, rad/s^2')
grid on
axis tight

% Plot gap vs time
f9 = figure;
plot(results2(:,1),results2(:,5)*1000)
grid on
axis tight
xlabel('Time, s')
ylabel('Gap Distance, mm')