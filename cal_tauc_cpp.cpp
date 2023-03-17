#include <vector>
#include <cmath>

extern "C" {
    float cal_tauc_cpp(float *data, int npts, float df, float sat_t, float end_t) {
        std::vector<float> t(npts);
        for (int i=0; i<npts; i++) {
            t[i] = i / df;
        }
        std::vector<bool> ind_range(npts);
        for (int i=0; i<npts; i++) {
            ind_range[i] = (t[i] < end_t) && (t[i] > sat_t);
        }
        float r_num = 0.0;
        float r_den = 0.0;
        for (int i=1; i<npts; i++) {
            if (ind_range[i]) {
                float x = data[i] - data[i-1];
                r_num += x * x * df;
                r_den += data[i] * data[i];
            }
        }
        float r = r_num / r_den;
        return 2 * M_PI / sqrt(r);
    }
}
