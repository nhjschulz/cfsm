[![License](https://img.shields.io/badge/license-MIT-blue.svg)](http://choosealicense.com/licenses/mit/)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
![example workflow](https://github.com/nhjschulz/cfsm/actions/workflows/cmake-single-platform.yml/badge.svg)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/nhjschulz/library/CFSM.svg)](https://registry.platformio.org/libraries/nhjschulz/CFSM)
[![arduino-library-badge](https://www.ardu-badge.com/badge/CFSM.svg?)](https://www.ardu-badge.com/CFSM)

# CFSM - A State Design Pattern for State Machines in C-Language.

Finite state machines (FSM) are present in almost every non trivial program.
Guides on how to implement them are part of many programming
tutorials. But these tutorials focus around the
[STATE Design Pattern](https://en.wikipedia.org/wiki/State_pattern)
for <b>object oriented languages</b> like C++, Java or C# only.

CFSM follows a simplistic approach for the C-Language to implement
maintainable state machines according to the STATE design pattern.
This differentiates it from other solutions that often rely on complex
macros to construct state handlers.

This work was inspired by the excellent article
[Patterns in C- Part 2: STATE](https://www.adamtornhill.com/Patterns%20in%20C%202,%20STATE.pdf) from Adam Petersen.

## Introducing CFSM

The CFSM Github project contains both
the CFSM source code and an easy to understand example. It is build using
[CMake](https://cmake.org). <br>
Integration into own projects doesn't require CMake. CFSM is a single source
and header file only. There are no external dependencies. Simply add the
[c_fsm.c and c_fsm.h](https://github.com/nhjschulz/cfsm/tree/master/src)
files into your project.

## How It Works

CFSM is following the State design pattern without using object oriented
constructs.

![State Pattern](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/cfsm_statepattern.puml)

The state pattern builds on
* A context that delegates operations to one of various state objects,
  which is currently the active state.
* A number of state objects that implement context operations to provide
  state dependent behavior of these operations.

### The CFSM Context

A CFSM context defines a fixed set of operations. These operations got defined
with the following UML State diagram in mind. It covers a wide range of
use cases:

![State Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/cfsm_context.puml)

There are operations to execute
   1. When the FSM "enters" a state, meaning it becomes the current active one.
   2. When the FSM "leaves" a state, meaning some other state becomes active
   3. When a cyclic processing in the active state shall take place
   4. When an event is signaled to the FSM

Each of these operations is represented as a function pointer in the CFSM
context data structure. CFSM takes care about calling leave and enter
operations during a state transition. The cyclic process and event signaling
gets triggered by the application through CFSM public API.

A void pointer called ```ctxPtr``` is part of the context in addition to
the operation function pointers. This pointer is set by ```cfm_init()``` and
can be used in an application specific way. FSM does not use it by itself.
The ```ctxPtr``` is intended to support multiple FSM instances with the same
handler functions. The handlers can use the pointer to access instance
specific data.

The CFSM context structure definition is:

```c
typedef void (*cfsm_TransitionFunction)(struct cfsm_Ctx * fsm);
typedef void (*cfsm_EventFunction)(struct cfsm_Ctx * fsm, int eventId);
typedef void (*cfsm_ProcessFunction)(struct cfsm_Ctx * fsm);
typedef void *cfsm_InstanceDataPtr;

/** CFSM context operations */
typedef struct cfsm_Ctx {
    cfsm_InstanceDataPtr    ctxPtr;    /**< context instance data     */
    cfsm_TransitionFunction onLeave;   /**< operation run on leave    */
    cfsm_ProcessFunction    onProcess; /**< cyclic operations         */
    cfsm_EventFunction      onEvent;   /**< report event to the state */
} cfsm_Ctx;

```

Notes:
 * All operations in a state are optional, with the exception of the enter
   operation. A state that cannot be entered is pointless.
 * Operations that are not defined in a state are ignored by CFSM.
 * Supporting "other" operations can be done by adding new, or
   changing existing functions pointers in the context. CFSM
   is primarily an implementation pattern, not a fixed function library.

### CFSM States

A CFSM state is a light weight concept. It is not implemented as
an object or data structure as someone would expect using object
oriented languages. A state in the C-Language world is just a set of
functions that are known by the context as operations.

The only mandatory state function is the enter operation. It is needed
even if there are no state specific entry actions to perform. It's job is
to also update the context function pointers. Below is an example of a
set of function that define a SuperMario state:

```c
static void SuperMario_onProcess(cfsm_Ctx * fsm) { /* ... */}
static void SuperMario_onLeave(cfsm_Ctx * fsm) { /* ... */}
static void SuperMario_onEvent(cfsm_Ctx * fsm, int eventId) { /* ...*/}


void SuperMario_onEnter(cfsm_Ctx * fsm)
{
    fsm->onProcess = SuperMario_onProcess;
    fsm->onEvent = SuperMario_onEvent;
    fsm->onLeave = SuperMario_onLeave;
    /* ... */

}
```

### CFSM State Transitions

State transitions are triggered by calling the ```cfsm_transition()```
API function. The call can originate

1. from the CFSM using application to enter a specific state
2. from inside the state operation handlers

The following interaction diagram shows what happens during a state
transition from state "Mario" to "SuperMario":

![Transition Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/cfsm_transition.puml)

The process() calls are not part of the transition. They show how
the delegation of the process action changed as a result of the
state transition in between.

## Examples

The remainder of this document walks through the Mario example to
demonstrate CFSM usage. There is also a working CFSM version of the
Arduino blink sketch worth a look. It is available from
[https://github.com/nhjschulz/cfsm/tree/master/examples/UnoBlink](https://github.com/nhjschulz/cfsm/tree/master/examples/UnoBlink). This minimal example
is suitable as a boilerplate for own CFSM based application experiments.

# The Mario CFSM Example

In this chapter we use the CFSM pattern to simulate the life cycle of the
famous Mario computer game character that most people should be familiar with.

## The Mario State Machine

Mario can change his appearance into various different characters to gain
super powers. He starts as small Mario without powers. He changes
to a different appearance with a specific power by collecting items.
Mario earns coins by collecting items and gets an additional life
if he collects more than 5000 of them.
If an empowered Mario hits a monster, he loses the power and changes
back to small Mario. If small Mario hits a monster, he loses a life. If
no more lives are available, the game ends.

This means we have a fixed set of states (characters) and rules (items)
that define how to switch between them. This is a FSM! We can model
it like this:

![Mario State Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/mario_states.puml)

Here are the transitions shown as a table:

| Character  | Item       | Effect            | Coins |
|------------|------------|-------------------|-------|
|Small Mario |Mushroom    |Become Super Mario | +100  |
|Small Mario |Fire Flower |Become Fire Mario  | +200  |
|Small Mario |Feather     |Become Cape Mario  | +300  |
|Small Mario |Monster     |Loose a Life       |       |
|Super Mario |Fire Flower |Become Fire Mario  | +200  |
|Super Mario |Feather     |Become Cape Mario  | +300  |
|Super Mario |Monster     |Become Small Mario |       |
|Fire Mario  |Feather     |Become Cape Mario  | +300  |
|Fire Mario  |Monster     |Become Small Mario |       |
|Cape Mario  |Fire Flower |Become Fire Mario  | +200  |
|Cape Mario  |Monster     |Become Small Mario |       |

## Example Implementation

The example uses CFSM to implement the Mario state machine in the following
way:

  * Each Mario character is a state implemented in an own C-File.
  * The collection of items or the monster hits are modelled as events.
  * The process operation prints a character specific message.
  * The enter/leave operations print a message to visualize these transitions.

The main loop of the example implements a small menu where events get
fired based on user input to simulate the game.

This is the example application component design:

![Mario Example Class Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/doc/mario_classdiagram.puml)


### The Main function

The main function implements the game simulation loop. It owns
a CFSM instance as a local cfsm_Ctx structure called ``marioFsm``.

The CFSM setup phase consists of initializing ``marioFsm`` and
then transition to Mario's start state "SmallMario". The simplified
codes looks like this:

 ```c
#include "c_fsm.h"
#include "states/small_mario.h"

int main(int argc, char **argv)
{
    cfsm_Ctx marioFsm;

    cfsm_init(&marioFsm, NULL);
    cfsm_transition(&marioFsm, SmallMario_onEnter);

    /* ... */
 ```

This example doesn't use instance data and passes NULL for it
in the call to ```cfsm_init()```. Instance data could be used to
extend the game to support multiple players by adding
a Luigi. We can then run two FSMs in parallel with the same
handlers.

Transitioning to the start state is done by providing the
enter operation handler for this state to the API function
``cfsm_transition()``. CFSM then calls the leave operation
of the former state (if one was defined) and then calls the passed
enter operation.

The remainder of the main function is the game loop. It gives Mario
a process operation cycle by calling
``cfsm_process(&marioFsm)``. The process handlers in this example
only print a message according to Mario's current state to
show that they had been run.<br>
The loop then displays a menu asking to enter a key to trigger
the next event. This event is passed to the Mario CFSM by calling
``cfsm_event()``. <br>
Finally the loop restarts unless QUIT was selected by the user.

 ```c
    for(;;)
    {
        int option;

        /* perform process cycle in current CFSM state.*/
        cfsm_process(&marioFsm);

        mario_print(); /* show Mario's data*/

        printf("\nChoose Event: (1=Mushroom, 2=FireFlower, 3=feather, "
               "4=Monster, 5=none (just process), 0=quit) : ");
        while ((scanf("%d", &option) != 1) || (option > 5))
        {
            puts("invalid option");
        }

        if (QUIT == option) {
            break;
        }

        /* process signal in current CFSM state */
        if (NOP != option)
        {
            cfsm_event(&marioFsm, option);
        }
    }
 ```

That's it. There is no special state processing in the application
main loop. It's only purpose is to initialize, process and signal
events to CFSM. Any state dependent code vanishes into the
different state implementing modules.

Here is a transcript of first game simulation steps:

 ```
 $ cfsm_mario.exe
(1) SmallMario_onEnter()...
(2) SmallMario_onProces(): It's me, Mario!
(3) Mario: Variant: SmallMario Lifes: 3  Coins: 0

(4) Choose Event: (1=Mushroom, 2=FireFlower, 3=feather, 4=Monster, 5=none (just process) 0=quit) : 1
(5) SmallMario_onLeave() ...
(5) SuperMario_onEnter()...
(6) SuperMario_onProces(): It's me, SUPER Mario!
(7) Mario: Variant: SuperMario Lifes: 3  Coins: 100

(8) Choose Event: (1=Mushroom, 2=FireFlower, 3=feather, 4=Monster, 5=none (just process) 0=quit) :
 ```

1. This is the response of the initial transition to small Mario. Note that
   there is no leave message as CFSM had no former state.
2. This is the response to the process cycle we trigger at the begin of
   the game loop.
3. This is main printing the current Mario state. It is not related to CFSM.
4. This is the menu, asking for user input. We gave it a 1 (MUSHROOM).
5. Processing the MUSHROOM event causes a transition inside the event
   operation of SmallMario. We leave SmallMario state into SuperMario.
6. Now the loop restarted with the process cycle. Note that we became
   SUPER Mario :).
7. Also Mario's data got updated. It shows now SuperMario and the earned
   100 coins.
8. The game loop askes again for the next user input

### The Event States Implementation

All states from the example are implemented in an own C module in the
src/example/states folder. There is no requirement to do it this way,
but its a reasonable way to keep things maintainable if state complexity
or number increases over time. The following sub chapters walk through
the operation handlers of the small Mario state. The other states are
very similar and not shown here. Also remember that a CFSM state is just
a set of operation handler functions.

#### The Small Mario Enter Operation

The enter function is the only mandatory operation handler for a state
and the only one that needs to be public. This is necessary to allow
other modules to transition into it.

 ```c
 void SmallMario_onEnter(cfsm_Ctx * fsm)
{
    puts("SmallMario_onEnter()...");

    mario_setVariant(SMALL_MARIO);

    fsm->onProcess = SmallMario_onProcess;
    fsm->onEvent = SmallMario_onEvent;
    fsm->onLeave = SmallMario_onLeave;
}
 ```

 The enter operation gets the CFSM context passed as a pointer. This
 is required to update the handler pointers to use the new states
 operations.

 The first two lines are the actions that the enter handler performs.
 In this example it

 * prints a message to show the user it got called. In real code such
   a call would not be there or would be using some debug logging api.
 * updates our Mario to become a small one.

The final 3 lines update the CFSM context to delegate operations
to the SmallMario state.

Note that unused handlers don't need to be set to NULL. The
``cfsm_transition()`` API has done this before calling the
enter operation. Only the needed handlers must be set here
(if any).

#### The Small Mario Leave Operation

Our example leave operations are trivial. We have no actions to perform
according to the Mario state machine. They just print a line to indicate
to the user when they got called.

```c
static void SmallMario_onLeave(cfsm_Ctx * fsm)
{
    puts("SmallMario_onLeave() ...");
}
 ```

#### The Small Mario Process Operation

Our process operations are also trivial. They just print a line
that fits to the current Mario personality.

In real applications you have to make a decision what to do during
cyclic processing or event signaling. Our Mario model is event
driven. That's why the transition logic and action where placed into
the event operation handler. If your logic follows a polling model,
you likely implement this in the processing operation instead.

```c
static void SmallMario_onProcess(cfsm_Ctx * fsm)
{
    puts("SmallMario_onProces(): It's me, Mario!");
}
 ```

#### The Small Mario Event Signal Operation

The onEvent operation is the working horse in our example Mario state
machine due to the fact that all transitions are event based. The
event signal operation is implemented as a switch over the event ids.

The call to ``mario_updateCoins()`` extracts the coin awards into
a helper function. The amount of coins depend on the event, not
on the state. Directly implementing it inside the states would cause
code dublication.

The individual event cases trigger a transition from small to another
Mario dependent on the event. Noteworthy is the slightly more complex
monster case. Here we also need to decrease the number of lives
and eventually transition into dead Mario if no more are left.

```c
static void SmallMario_onEvent(cfsm_Ctx * fsm, int eventId)
{
    mario_updateCoins(eventId);

    switch(eventId)
    {
        case MUSHROOM:
            cfsm_transition(fsm, SuperMario_onEnter);
            break;

        case FIREFLOWER:
            cfsm_transition(fsm, FireMario_onEnter);
            break;

        case FEATHER:
            cfsm_transition(fsm, CapeMario_onEnter);
            break;

        case MONSTER:
            if (0 == mario_takeLife())
            {
                cfsm_transition(fsm, DeadMario_onEnter);
            }
            break;
    }
}
 ```

This is now a good time to look into the other Mario [state
implementations](https://github.com/nhjschulz/cfsm/tree/master/examples/mario/states)
to figure out how they differ from SmallMario.
The DeadMario state is the most deviating one. There is no way
back from the after live, meaning some operation handlers are
not needed and therefore also not present at all.

# Conclusion

The CFSM pattern is surprisingly simple. There are no complex logic
sequences or loops in CFSM. Processing boils down to a NULL checked
function pointer call to delegate operation requests to state
dependend handlers. This simplicity makes the pattern also usable 
for functional safety applications. The functionality is easy to
test and review.

## Benefits

CFSM achieves the following benefits

1. Shows a light weight method to implement the STATE pattern in plain C
   language.
2. Avoids complex and nested conditional logic by distributing it
   into different states that are easier to maintain.
3. Encapsulates state specific behavior into the states implementation.
4. Easy to extend with new states. Adding new states affect the
   existing code in a minimal way. Only transitions to the new state
   need to be added somewhere.

## Drawbacks

1. The separation into states increases the number of modules to deal with.
   This may cause unreasonable overhead for trivial state machines that are
   better implemented using nested conditional logic.
2. State implementations typically look very similar, causing some degree of
   code duplication. This is usually addressed in OO Languages by introducing
   base classes for states. C-Language doesn't offer such concepts and
   CFSM does not try to mimic such OO behavior in C-language.

