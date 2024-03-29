#ifndef APPLICATION_H
#define APPLICATION_H
#include <string>

struct GLFWwindow;

/// Application class:
/// * init OpenGL
/// * provide:
///   * getWidth()
///   * getHeight()
///   * getFrameDeltaTime()
///   * getWindowRatio()
///   * windowDimensionChanged()
/// * let the user define the "loop" function.
class Application {
public:
  Application();

  static Application &getInstance();

  // get the window id
  GLFWwindow *getWindow() const;

  // window control
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  // application run
  void run();

  // Application informations
  //
  int getWidth();
  int getHeight();
  float getWindowRatio();
  bool windowDimensionChanged();

private:
  enum State { stateReady, stateRun, stateExit };

  State state;

  Application &operator=(const Application &) { return *this; }

  GLFWwindow *window;

  // Time:
  float time;
  float deltaTime;

  // Dimensions:
  int width;
  int height;
  bool dimensionChanged;
  void detectWindowDimensionChange();

protected:
  Application(const Application &){};

  std::string title;

  virtual void loop() = 0;
};

#endif