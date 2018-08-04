#include <vector>
#include <functional>
#include <assert.h>

using std::vector;
using std::function;

template <typename T>
using Matrix = vector<vector<T>>;

template <typename T>
using Activator = function<T(T)>;

struct Transform {
    Transform(vector<double>* in, vector<double>* out)
         : input_(in), output_(out) {
        assert(input_);
        assert(output_);
        M_ = input_->size();
        M_ = output_->size();
        // weight matrix should be N rows, M cols
        weight_.resize(N_);
        for (size_t i = 0; i < N_; i++) {
            weight_[i].resize(M_);
        }
    }

    void compute(const vector<double>* in = nullptr, vector<double>* out = nullptr) {
        if (in != nullptr) {
            input_ = const_cast<vector<double>*>(in);
            assert(input_);
        }
        if (out != nullptr) {
            output_ = out;
            assert(output_);
        }
        for (size_t i = 0; i < N_; i++) {
            double y = 0;
            for (size_t j = 0; j < M_; j++) {
                y += weight_[i][j] * (*input_)[j];
            }
            (*output_)[i] = activator_ ? activator_(y) : y;
        }
    }

    size_t M_, N_;
    vector<double>* input_;
    vector<double>* output_;
    vector<double> biaes_;
    Matrix<double> weight_;
    Activator<double> activator_;
};

struct Net {
    vector<double> input_;
    vector<double> hidden_;
    vector<double> output_;
    Transform i2h_;
    Transform h2o_;

    Net()
      : i2h_(&input_, &hidden_)
      , h2o_(&hidden_, &output_)
    {}
    ~Net() {}

    void compute(const vector<double>& in, vector<double>* out) {
        i2h_.compute(&in, &hidden_);
        h2o_.compute(&hidden_, &output_);
    }

    void traning(const vector<double>& in, const vector<double>& out) {

    }
};

int main()
{
    return 0;
}