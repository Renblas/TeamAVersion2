// Class Definition

class customTimer
{
public:
    // variables
    float time = 0;
    float maxTime = 0;
    // functions
    customTimer(float max);
    void update();
    void reset();
    bool done();
};

/*
 *   Custom Timer class definitions
 */

customTimer::customTimer(float max)
{
    maxTime = max;
    time += maxTime;
}
void customTimer::update()
{
    if (time > 0)
    {
        time -= ((float)20 / (float)1000);
    }
}
bool customTimer::done()
{
    if (time <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void customTimer::reset()
{
    time += maxTime;
}