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

The `riot-saul-coap` package gets included with the following lines in
the `Makefile` (everything else in the Makefile is specific to this
app):

``` makefile
USEMODULE += riot-saul-coap
EXTERNAL_MODULE_DIRS += $(CURDIR)/riot-saul-coap
```

The header files of the `riot-saul-coap` module are:

``` c++
#include "saul_coap.h"
#include "saul_cord_ep.h"
```

These define the following setup / init functions, that can be used to
use the module:

``` c++
saul_coap_init();

saul_cord_ep_register_cb(_on_ep_event);
saul_cord_ep_create(CORD_EP_ADDRESS);
saul_cord_ep_run();
```

See [main.c](main.c) as an example usage file.

[the external module test]: https://github.com/RIOT-OS/RIOT/tree/master/tests/external_module_dirs

[riot-saul-coap]: https://github.com/rosetree/riot-saul-coap

[inet]: http://inet.haw-hamburg.de/teaching/ws-2019-20/riot-im-internet-of-things
