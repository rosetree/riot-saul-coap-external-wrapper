#include "winch.h"
#include "net/gcoap.h"


static ssize_t _winch_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);

/* CoAP resources. Must be sorted by path (ASCII order). */
static const coap_resource_t _resources[] = {
    { "/winch", COAP_POST, _winch_handler, NULL },
};

static gcoap_listener_t _listener = {
    &_resources[0],
    sizeof(_resources) / sizeof(_resources[0]),
    NULL,
    NULL
};

winch_t *pwinch;

static ssize_t _winch_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx)
{
    uint8_t l_ges;

    (void)ctx;
   
   //change payload size  from 5 to 9- according to expected parameters etc.
    if (pdu->payload_len <= 9) {
        char req_payl[10] = { 0 };
        memcpy(req_payl, (char *)pdu->payload, pdu->payload_len);

        l_ges = atoi(req_payl);
    }
    else {
        return gcoap_response(pdu, buf, len, COAP_CODE_BAD_REQUEST);
    }
    size_t resp_len;
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
   /* option of text and cbor format*/
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    //coap_opt_add_format(pdu, COAP_FORMAT_CBOR);
    resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

	//variable initiations?
            winch_control(pwinch, l_ges);
            resp_len = gcoap_response(pdu, buf, len, COAP_CODE_404);
	    return resp_len;
    }

void winch_coap_init(winch_t *winch)
{
    pwinch = winch;
    gcoap_register_listener(&_listener);
}