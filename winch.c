

static int set(const void *dev, phydat_t *data)
{
   const winch_saul_driver *w = (const 			_saul_driver *) dev;
   winch_set();
   return 1;
}

const saul_driver_t winch_saul_driver = {
   .read = saul_notsup,
   .write = set,
   .type = SAUL_ACT_SERVO
};

static ssize_t _saul_winch_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx)
{
    uint8_t type;

    (void)ctx;
   
   //change payload size - according to expected parameters etc.
    if (pdu->payload_len <= 5) {
        char req_payl[6] = { 0 };
        memcpy(req_payl, (char *)pdu->payload, pdu->payload_len);
        type = atoi(req_payl);
    }
    else {
        return gcoap_response(pdu, buf, len, COAP_CODE_BAD_REQUEST);
    }

    return _servo_type_responder(pdu, buf, len, type);
}

static ssize_t _winch_type_responder(coap_pkt_t* pdu, uint8_t *buf, size_t len, uint8_t type)
{
    saul_reg_t *dev = saul_reg_find_type(type);
    phydat_t res;
    phydat_t data;
    int dim;
    size_t resp_len;
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
   /* option of text and cbor format*/
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    //coap_opt_add_format(pdu, COAP_FORMAT_CBOR);
    resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (dev == NULL) {
        char *err = "device not found";
        if (pdu->payload_len >= strlen(err)) {
            memcpy(pdu->payload, err, strlen(err));
            resp_len += gcoap_response(pdu, buf, len, COAP_CODE_404);
            return resp_len;
        }
        else { 
            //functions to execute : winch_control (winch_t *winch, int l_ges)
             return gcoap_response(pdu, buf, len, COAP_CODE_404);
        }
    }
    if (dim <= 0) {
        char *err = "no values found";
        if (pdu->payload_len >= strlen(err)) {
            memcpy(pdu->payload, err, strlen(err));
            resp_len += gcoap_response(pdu, buf, len, COAP_CODE_404);
            return resp_len;
        }
        else {
            return gcoap_response(pdu, buf, len, COAP_CODE_404);
        }
    }
    /* write the response buffer with the request device value */
    resp_len += fmt_u16_dec((char *)pdu->payload, res.val[0]);
    return resp_len;
}
