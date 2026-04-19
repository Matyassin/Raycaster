#include <random>

static float RandomFloat(float start = 0.0f, float end = 1.0f)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(start, end);

    return dist(rng);
}
