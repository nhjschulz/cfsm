[![License](https://img.shields.io/badge/license-MIT-blue.svg)](http://choosealicense.com/licenses/mit/)
[![Repo Status](https://www.repostatus.org/badges/latest/wip.svg)](https://www.repostatus.org/#wip)
![example workflow](https://github.com/nhjschulz/cfsm/actions/workflows/cmake-single-platform.yml/badge.svg)

# CFSM -  A State Pattern Approach for C-Programs

A C-Language implementation pattern for finite state machines

Finite state machines are present in almost every non trivial program.
Guides on how to implement them are a standard part of many programming
tutorials. But these tutorials focus mostly around the 
[STATE Design Pattern](https://en.wikipedia.org/wiki/State_pattern) 
for object oriented languages like C++, Java or C#.

The CFSM project uses a light weight C-Language approach that is suitable
for any kind of application, including resource constraints embedded 
systems using micro controllers.

This work was inspired by the excellent article
[Patterns in C- Part 2: STATE](https://www.adamtornhill.com/Patterns%20in%20C%202,%20STATE.pdf) from Adam Petersen.

## Introducing CFSM

This project contains both the CFSM source code and a easy to understand
example that shows how to use it. It is build using CMake. Integration into
own project doesn't rely on CMake. CFSM is a single source file and 
header file with names c_fsm.h and c_fsm.c only. You only need to add these
two files into your project.

## How It Works

CFSM is following the state design pattern without using object oriented
constructs.

![](https://upload.wikimedia.org/wikipedia/commons/e/ec/W3sDesign_State_Design_Pattern_UML.jpg)

Source: [Wikipedia](https://en.wikipedia.org/wiki/State_pattern)
by [VanderJoe](https://commons.wikimedia.org/wiki/User:Vanderjoe )
licensed under [CC BY 4.0](https://creativecommons.org/licenses/by-sa/4.0)

The state pattern builds on 
* A context that delegates operations to one of the various state objects,
  which is currently the active state.
* A number of states objects the expose the context operations and 
  encapsulate state dependent behavior of the operations.
* A communication from states to the context that allow to change the current
  active state.

### The CFSM Context

The CFSM context defines a fixed set of operations. These operations got defined
with the following UML State diagram in mind: 

![State Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/cfsm_context.puml)

There are operations to execute
   1) When the FSM "enters" a state, meaning it becomes the current active one.
   2) When the FSM "leaves" a state, meaning some other state gets active
   3) When a cyclic processing in the active state shall take place
   4) When an event is signaled to a state

Each of these operations is represented as a function pointer inside the FSM
context data structure. CFSM takes care about calling the leave and enter 
operations during a state transition. The cyclic process and event signaling
gets triggered by the application through CFSM public API. The structure
definition is simple (besides the function pointer syntax):

```C
typedef void (*cfsm_TransitionFunction)(struct cfsm_Fsm * state);
typedef void (*cfsm_EventFunction)(struct cfsm_Fsm *state, int eventId);
typedef void (*cfsm_ProcessFunction)(struct cfsm_Fsm *state);

/** CFSM context operations */
typedef struct cfsm_Fsm {
    cfsm_TransitionFunction onEnter;   /**< operation run on enter    */
    cfsm_TransitionFunction onLeave;   /**< operation run on leave    */
    cfsm_ProcessFunction    onProcess; /**< cyclic operations         */
    cfsm_EventFunction      onEvent;   /**< report event to the state */
} cfsm_Fsm;

```


Notes:
 * All operations in a state are optional, with the exception of the enter
   operation. A state that cannot be entered is pointless. 
   Operations that are not defined in a state are ignored by CFSM.
 * Supporting "other" operations can be easily done by adding new, or
   changing existing functions pointers in the context.

### CFSM States

A CFSM state is a light weight concept. It is not an object or data structure
as someone would expect it in object oriented languages. A state in our 
C-Language world is just a set of functions that are known by the context 
as operations.

The only mandatory state function is the enter operation. It is needed
even if there are no state specific entry actions to perform. It jobs is
also to update the context function pointers. Below is an example of a 
set of function that define the SuperMario state:

```C
static void SuperMario_onProcess(cfsm_Fsm * fsm) { /* ... */}
static void SuperMario_onLeave(cfsm_Fsm * fsm) { /* ... */}
static void SuperMario_onEvent(cfsm_Fsm * fsm, int eventId) { /* ...*/}


void SuperMario_onEnter(cfsm_Fsm * fsm)
{
    fsm->onProcess = SuperMario_onProcess;
    fsm->onEvent = SuperMario_onEvent;
    fsm->onLeave = SuperMario_onLeave;
    /* ... */

}
```

### CFSM State Transitions

State transitions are triggered by calling the cfsm_transitionTo()
API function. The call can originate either 

1) from the user of the FSM to enter a specific state
2) from inside the state operation handlers

The following interaction diagram shows what happens during a state
transition from state "Mario" to "SuperMario":

![Transition Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/cfsm_transition.puml)

The process() calls are not part of the transition. They show how
the delegation of the process action changes as a result of the 
state transition in between.

# The Mario CFSM Example

<b>TODO</b>
