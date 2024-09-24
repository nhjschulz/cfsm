# Arduino Blink with CFSM

This is a boilerplate code example for
[CFSM](https://github.com/nhjschulz/cfsm) based applications. 
It is build on top of Arduino and implements a CFSM version of
the "led-blink" sketch, the embedded system version of
"hello world". It gets build using 
[PlatformIO](https://platformio.org/) and is configured for
Arduino UNO. But it will run on any Arduino supported platform
with an onboard led by updating ```platform.ini```.

## Blinking with a State Machine

The blink sketch toggles a led on or off, resulting in 
two distinct states that can be mapped to FSM states. The
first is representing "On", the second "Off". The transitions
between the states happen after fixed time intervals. In
this example we use one second.

To make this simple logic a bit more interesting, we use
different transition methods for going to on or off.

* The On state is entered based on an event from
  the main ```loop()``` function. This event is signaled
  every 2 seconds.

* The On state remains active for one second and then
  transitions back to the Off state.

![State Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/examples/UnoBlink/doc/BlinkState.puml)

## CFSM Blink Example

The example is based on PlatformIO 's Arduino template with a main module 
implementing the ```setup()``` and ```loop()``` methods. 
It includes CFSM as an external library using the ```lib_deps``` variable in
```platformio.ini```.

~~~{.ini}
lib_deps =
    nhjschulz/CFSM@^0.2.0
~~~

The example is following this SW architecture:

### Static Structure

![State Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/examples/UnoBlink/doc/BlinkClass.puml)

### Arduino Setup Sequence

![Setup Sequence Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/examples/UnoBlink/doc/BlinkSetup.puml)

### Arduino Loop Transition into OffState 

The sequence starts while CFSM is in OnState:

![Setup Sequence Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/examples/UnoBlink/doc/BlinkOnToOff.puml)

## Arduino Loop Transition into OnState 

The sequence starts while CFSM is in OffState:

![Setup Sequence Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/nhjschulz/cfsm/master/examples/UnoBlink/doc/BlinkOffToOn.puml)

Note that there is a little difference between the transitions:
*  "On" state processes the transition inside the process operation.
*  "Off" state does not use the process operation. The state works event based. That's why
   CFSM instantly returns on the process() request in this state.

## Running the Example

The onboard led will toggle on and off after every second
when the example got flashed. Serial monitor prints
will print the progress also to a serial port. The 
output looks like this:

~~~
OnState: enter()
OnState: LED On time has expired !
OnState: leave()
OffState: enter()
main: turn on time reached
OffState: onEvent(42)
OffState: leave()
OnState: enter()
...
~~~

