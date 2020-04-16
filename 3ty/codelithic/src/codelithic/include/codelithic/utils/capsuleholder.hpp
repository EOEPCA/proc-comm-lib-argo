
#ifndef CODELITHIC_CAPSULEHOLDER_HPP
#define CODELITHIC_CAPSULEHOLDER_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

namespace codelithic {
template <typename T>
class CapsuleHolder {
 private:
  class Capsule final {
   public:
    explicit Capsule(T *p) : t(p), id(""), dependFrom{}, level(0) {}

    Capsule() : t(nullptr), id(""), dependFrom{}, level(0) {}

    Capsule(T *p, std::string id)
        : t(p), id(std::move(id)), dependFrom{}, level(0) /*, maxLevel(0)*/ {}

    ~Capsule() { t = nullptr; }

    bool isValid() { return (t != nullptr && !id.empty()); }

    void upLevel(Capsule *bp) {
      if (bp) {
        int theLevel = bp->getLevel();
        if (theLevel >= level) {
          level = bp->getLevel();
          Capsule::operator++();
        }
      }
    }

    Capsule &operator++()  // ++A
    {
      level++;
      return *this;
    }

    Capsule &operator--()  // --A
    {
      level--;
      if (level < 0) {
        level = 0;
      }

      return *this;
    }

    explicit operator int() const { return level; }

    explicit operator std::string() const { return id; }

    //        Capsule & operator << (T* val){
    //            t=val;
    //            return *this;
    //        }
    //        Capsule &operator<<(const std::string &val) {
    //            id=val;
    //            return *this;
    //        }

    /***
     * depend!
     * @param dep
     * @return
     */
    Capsule &operator>>(const std::string &dep) {
      if (dep != id) {  // ignoro se dipernde da se stesso
        auto res = std::find(dependFrom.begin(), dependFrom.end(), dep);
        if (res == dependFrom.end()) {
          dependFrom.emplace_back(dep);
        }
      }
      return *this;
    }

    void setId(const std::string &theId) { Capsule::id = theId; }

    const std::string &getId() const { return id; }

    const std::list<std::string> &getDependFrom() const { return dependFrom; }

    int getLevel() const { return level; }

    void setLevelZero() { level = 0; }

    T *getTemplate() { return t; }

   private:
    T *t;
    std::string id;
    std::list<std::string> dependFrom{};
    int level;
  };

  int check(CapsuleHolder::Capsule *brick) {
    auto dep = brick->getDependFrom();
    for (auto &d : dep) {
      auto item =
          std::find_if(capsuleHolder.begin(), capsuleHolder.end(),
                       [&d](const Capsule *act) { return act->getId() == d; });

      if (item != capsuleHolder.end()) {
        brick->upLevel(*item);
      } else {
        return 0;
      }
    }
    return 1;
  }

  void checkWheelbarrow(Capsule *brick, std::list<Capsule *> &wheelbarrow) {
    std::list<Capsule *> toRemove;
    bool interaction;
    do {
      interaction = false;
      for (auto &d : wheelbarrow) {
        if (!check(d)) {
        } else {
          interaction = true;
          capsuleHolder.push_back(d);
          toRemove.push_back(d);
        }
      }

      if (!toRemove.empty()) {
        for (auto &p : toRemove) {
          wheelbarrow.remove(p);
        }
      }
    } while (interaction);
  }

  void go(CapsuleHolder::Capsule *brick, std::list<Capsule *> &wheelbarrow,
          int nRows) {
    if (!brick) {
      return;
    }

    auto dep = brick->getDependFrom();
    if (dep.empty()) {
      brick->setLevelZero();
      capsuleHolder.emplace_back(brick);
    } else {
      if (!check(brick)) {
        brick->setLevelZero();
        wheelbarrow.emplace_back(brick);
      } else {
        capsuleHolder.emplace_back(brick);
      }
    }

    checkWheelbarrow(brick, wheelbarrow);
    if ((wheelbarrow.size() + capsuleHolder.size()) == nRows) {
      if (wheelbarrow.size() > 0) {
        throw std::runtime_error("Inconsistent dependencies");
      }
    }
  }

  void parse() {
    int rows = chain.size();
    this->capsuleHolder.clear();
    std::list<Capsule *> wheelbarrow{};
    if (!chain.empty()) {
      for (auto &b : chain) {
        go(b, wheelbarrow, rows);
      }
    }
  }

 public:
  CapsuleHolder() : lastBrick(nullptr) {}

  Capsule *plug() { return nullptr; }

  //    Capsule* operator()(){
  //        return new Capsule();
  //    }
  //
  //    Capsule* operator()(T*t){
  //        return new Capsule(t);
  //    }

  Capsule *operator()(T *t, const std::string &id) {
    return new Capsule(t, id);
  }

  int getMaxLevels() {
    int maxLevel{0};
    int level = 0;
    for (auto &capsule : capsuleHolder) {
      level = capsule->getLevel();
      if (level > maxLevel) {
        maxLevel = level;
      }
    }
    return (maxLevel + 1);
  }

  std::list<T *> getLevel(int level) {
    std::list<T *> res;
    for (auto &capsule : capsuleHolder) {
      if (capsule->getLevel() == level) {
        res.emplace_back(capsule->getTemplate());
      }
    }
    return res;
  }

  //    CapsuleHolder &operator<<(const std::string& val) {
  //    }

  //    CapsuleHolder &operator<<(T *t) {
  //    }

  CapsuleHolder &operator<<(CapsuleHolder::Capsule *capsule) {
    if (capsule) {
      if (capsule->isValid()) {
        std::string ID{(*capsule)};
        auto item = std::find_if(
            chain.begin(), chain.end(),
            [&ID](const Capsule *act) { return act->getId() == ID; });

        if (item == chain.end()) {
          chain.emplace_back(capsule);
          lastBrick = capsule;
        }
      } else {
        std::string err{"The capsule "};
        err.append(capsule->getId()).append(" is not valid");
        throw std::runtime_error(err);
      }
    } else {
      this->parse();
    }

    return *this;
  }

  ~CapsuleHolder() {
    lastBrick = nullptr;
    capsuleHolder.clear();
    for (auto &c : chain) {
      delete c;
    }
    chain.clear();
  }

 private:
  std::list<Capsule *> capsuleHolder{};
  std::list<Capsule *> chain{};
  Capsule *lastBrick{nullptr};

 private:
};
}  // namespace codelithic

#endif  // CODELITHIC_CAPSULEHOLDER_HPP
