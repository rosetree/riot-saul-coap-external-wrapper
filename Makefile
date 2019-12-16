APPLICATION = saul_coap_external

BOARD ?= native

RIOTBASE ?= $(CURDIR)/RIOT

USEMODULE += riot-saul-coap
EXTERNAL_MODULE_DIRS += $(CURDIR)/riot-saul-coap

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
