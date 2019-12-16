# External Module RIOT wrapper

This project tries to follow [the external module test][] in RIOT, to
implement [riot-saul-coap][] of the [RIOT in the Internet of Things
project][inet] as an external module.

After cloning this repository, please also clone the [RIOT][] code
base and the the [riot-saul-coap][] code base in the root directory of
this wrapper:

``` shellsession
$ git clone https://github.com/RIOT-OS/RIOT.git
Cloning into 'RIOT'...
... more lines ...
$ git clone https://github.com/rosetree/riot-saul-coap.git
Cloning into 'riot-saul-coap'...
... more lines ...
```

[the external module test]: https://github.com/RIOT-OS/RIOT/tree/master/tests/external_module_dirs

[riot-saul-coap]: https://github.com/rosetree/riot-saul-coap

[inet]: http://inet.haw-hamburg.de/teaching/ws-2019-20/riot-im-internet-of-things
