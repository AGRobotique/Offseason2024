#pragma once

class Subsystem {
 public:
  Subsystem() {}
  // virtual void resetSubsystem();
  virtual void updateSubsystem();
  virtual void initSubsystem();
  virtual ~Subsystem() {}
  //   bool isBeingUsed() { return m_isBeingUsed; }
  //   void setBeingUsed(bool isBeingUsed) { m_isBeingUsed = isBeingUsed; }

 private:
  //   bool m_isBeingUsed = false;
};