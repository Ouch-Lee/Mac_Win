#include "kf.h"

void KalmanFilter_init(KalmanFilter *kf, double pre_err, double mea_err) {
    kf->pre_err = pre_err;
    kf->mea_err = mea_err;
    kf->x = 0.0;
    kf->P = 1;
}

double KalmanFilter_update(KalmanFilter *kf, double measure) {
    double _x = kf->x;
    double _P = kf->P + kf->pre_err;
        
    kf->K = _P / (_P + kf->mea_err);
    kf->x = _x + kf->K * (measure - _x);
    kf->P = (1 - kf->K) * _P ;

    return kf->x;
}

void KalmanFilter_setX(KalmanFilter *kf, double new_measure) {
    kf->x = new_measure;
}
      
void KalmanFilter_track_fast(KalmanFilter *kf) {
    kf->pre_err = 16;
    kf->mea_err = 0.1;
}

void KalmanFilter_track_slow(KalmanFilter *kf) {
    kf->pre_err = 0.3;
    kf->mea_err = 16;
}
