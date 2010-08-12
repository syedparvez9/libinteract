#ifndef FSM_INC
#define FSM_INC

#include "WProgram.h"

class Fsm {
  typedef bool (*Cond) (void *);
  typedef void (*Action) (void *);
  
  struct Transition {
    int fromState, toState;
    Cond condition;
    Action action;
  };

  byte _nStates;
  byte _currentState;
  byte _initialState;
  Transition *_transitions;
  int _maxTransitions;
  int _nTransitions;
  
public:
  Fsm(byte nStates, byte initialState, int maxTransitions = 30)
    : _nStates(nStates), _initialState(initialState), _maxTransitions(maxTransitions), _nTransitions(0)
  {
    _transitions = (Transition *) malloc(_maxTransitions * sizeof(Transition));
    reset();
  }
  ~Fsm() {
    free(_transitions);
  }
  
  void reset() {
    _currentState = _initialState;
  }
  
  void transition(int fromState, int toState, Cond condition, Action action = 0) {
    if (_nTransitions < _maxTransitions)
      _transitions[_nTransitions++] = (Transition) { fromState, toState, condition, action };
  }
  
  void fire(void *input = NULL) {
    Transition *trans;
    for (int i=0; i<_nTransitions; i++) {
      trans = &_transitions[i];
      if (trans->fromState == _currentState &&
          trans->condition(input)) {
        if (trans->action)
          trans->action(input);
        go(trans->toState);
        break;
      }
    }
  }
  
  void go(int toState) {
    _currentState = toState;
  }
  
  int state() const {
    return _currentState;
  }
};

#endif
