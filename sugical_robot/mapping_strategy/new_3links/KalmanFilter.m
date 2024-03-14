classdef KalmanFilter
    properties
        pre_err % Q
        mea_err % R
        x       % 状态估计值
        P       % 状态估计误差的协方差矩阵
        x_temp  % 中间变量
        P_temp  % 中间变量
        K       % 卡尔曼增益
    end
    
    methods
        function obj = KalmanFilter(pre_err, mea_err)
            if nargin < 2
                obj.pre_err = 2;
                obj.mea_err = 16;
            else
                obj.pre_err = pre_err;
                obj.mea_err = mea_err;
            end
            obj.x = 0.0;
            obj.P = 1;
        end
        
        function new_measure = update(obj, measure)
            obj.x_temp = obj.x;
            obj.P_temp = obj.P + obj.pre_err;

            obj.K = obj.P_temp / (obj.P_temp + obj.mea_err);
            obj.x = obj.x_temp + obj.K * (measure - obj.x_temp);
            obj.P = (1 - obj.K) * obj.P_temp;
            new_measure = obj.x;
        end
        
        function obj = setX(obj, new_measure)
            obj.x = new_measure;
        end
        
    end
end
