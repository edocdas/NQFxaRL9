#include<iostream>

class Motor {
    double energy, resistance, current;
public:
    Motor(double E, double R, double I): energy(E), resistance(R), current(I) {}
    double runnableTime() const {
        return energy / (resistance * current * current);
    }
};

class Engine {
    double energy, performance;
public:
    Engine(double E, double P): energy(E), performance(P) {}
    double runnableTime() const {
        return energy / performance;
    }
};

class Hybrid: public Motor, public Engine {
  public:
    Hybrid(double ME, double MR, double MI, double EE, double EP):Motor(ME,MR,MI),  Engine(EE,EP) {
    }
    double runnableTime() const {
      double engine_time = Engine::runnableTime(), motor_time = Motor::runnableTime();
      return (engine_time > motor_time) ? motor_time : engine_time;
    }
};

int main(){
  Hybrid a(1,2,3,4,5);
  std::cout << a.runnableTime() << std::endl;
}
