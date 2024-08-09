#ifndef KF_H
#define KF_H

typedef struct {
    double pre_err; // Q
    double mea_err; // R

    double x;
    double P;
    double _x ;
    double _P; 
    double K; 
} KalmanFilter;

void KalmanFilter_init(KalmanFilter *kf, double pre_err, double mea_err);
double KalmanFilter_update(KalmanFilter *kf, double measure);
void KalmanFilter_setX(KalmanFilter *kf, double new_measure);
void KalmanFilter_track_fast(KalmanFilter *kf);
void KalmanFilter_track_slow(KalmanFilter *kf);

#endif
