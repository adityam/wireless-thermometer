function r = rmse(prediction,estimate)
% generalized function from Felix Heder http://www.mathworks.com/matlabcentral/fileexchange/21383-rmse/content/rmse.m
% Function to calculate root mean square error from a prediction vector or matrix 
% and the corresponding estimates.
% Usage: r = rmse(data,estimate)
% Note: predictions and estimates have to be of same size or estimate can be one
% number
% Example: r = rmse(randn(100,100),randn(100,100)) or r = rmse(randn(100,100),0)

if numel(estimate) == 1 && numel(prediction) > 1
    % delete records with NaNs in data first
    I = ~isnan(prediction);
else
    % delete records with NaNs in both datasets first
    I = ~isnan(prediction) & ~isnan(estimate); 
    estimate = estimate(I);    
end
prediction = prediction(I);
r = sqrt(mean((prediction(:)-estimate(:)).^2));