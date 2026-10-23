#ifndef RANDOM_H
#define RANDOM_H

class Random
{
public:
    static inline void Init(bool isRandomSeed = false)
    {
        generator.seed(isRandomSeed ? std::random_device{}() : 0);
    }

    static inline int Int(int a = 0, int b = 1) { return distInt(generator) % (b - a) + a; }
    static inline float Float(float a = 0, float b = 1) { return distFloat(generator) * (b - a) + a; }
    static inline double Double(double a = 0, double b = 1) { return distDouble(generator) * (b - a) + a; }

private:
    static inline auto generator = std::mt19937();
    static inline auto distInt = std::uniform_int_distribution<int>(0, INT_MAX);
    static inline auto distFloat = std::uniform_real_distribution<float>(0, 1);
    static inline auto distDouble = std::uniform_real_distribution<double>(0, 1);
};

#endif //RANDOM_H
