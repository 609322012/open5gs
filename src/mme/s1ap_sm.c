#define TRACE_MODULE _s1ap_sm

#include "core_debug.h"

#include "nas_message.h"
#include "gtp_message.h"

#include "mme_event.h"

#include "s1ap_build.h"
#include "s1ap_handler.h"

void s1ap_state_initial(fsm_t *s, event_t *e)
{
    d_assert(s, return, "Null param");

    mme_sm_trace(3, e);

    FSM_TRAN(s, &s1ap_state_operational);
}

void s1ap_state_final(fsm_t *s, event_t *e)
{
    d_assert(s, return, "Null param");

    mme_sm_trace(3, e);
}

void s1ap_state_operational(fsm_t *s, event_t *e)
{
    mme_enb_t *enb = NULL;

    d_assert(s, return, "Null param");
    d_assert(e, return, "Null param");

    mme_sm_trace(3, e);

    enb = mme_enb_find(event_get_param1(e));
    d_assert(enb, return, "Null param");

    switch (event_get(e))
    {
        case FSM_ENTRY_SIG:
        {
            break;
        }
        case FSM_EXIT_SIG:
        {
            break;
        }
        case MME_EVT_S1AP_MESSAGE:
        {
            s1ap_message_t *message = (s1ap_message_t *)event_get_param3(e);
            d_assert(message, break, "Null param");

            switch(message->direction)
            {
                case S1AP_PDU_PR_initiatingMessage :
                {
                    switch(message->procedureCode)
                    {
                        case S1ap_ProcedureCode_id_S1Setup :
                        {
                            s1ap_handle_s1_setup_request(enb, message);
                            break;
                        }
                        case S1ap_ProcedureCode_id_initialUEMessage :
                        {
                            s1ap_handle_initial_ue_message(enb, message);
                            break;
                        }
                        case S1ap_ProcedureCode_id_uplinkNASTransport :
                        {
                            s1ap_handle_uplink_nas_transport(enb, message);
                            break;
                        }
                        case S1ap_ProcedureCode_id_UECapabilityInfoIndication :
                        {
                            s1ap_handle_ue_capability_info_indication(
                                    enb, message);
                            break;
                        }
                        case S1ap_ProcedureCode_id_UEContextReleaseRequest:
                        {
                            s1ap_handle_ue_context_release_request(
                                    enb, message);
                            break;
                        }
                        default:
                        {
                            d_warn("Not implemented(choice:%d, proc:%d)",
                                    message->direction, message->procedureCode);
                            break;
                        }
                    }

                    break;
                }
                case S1AP_PDU_PR_successfulOutcome :
                {
                    switch(message->procedureCode)
                    {
                        case S1ap_ProcedureCode_id_InitialContextSetup :
                        {
                            s1ap_handle_initial_context_setup_response(
                                    enb, message);
                            break;
                        }
                        case S1ap_ProcedureCode_id_UEContextRelease :
                        {
                            s1ap_handle_ue_context_release_complete(
                                    enb, message);
                            break;
                        }
                        default:
                        {
                            d_warn("Not implemented(choice:%d, proc:%d)",
                                    message->direction, message->procedureCode);
                            break;
                        }
                    }
                    break;
                }
                case S1AP_PDU_PR_unsuccessfulOutcome :
                default:
                {
                    d_warn("Not implemented(choice:%d, proc:%d)",
                        message->direction, message->procedureCode);
                    break;
                }
            }

            break;
        }
        default:
        {
            d_error("Unknown event %s", mme_event_get_name(e));
            break;
        }
    }
}

void s1ap_state_exception(fsm_t *s, event_t *e)
{
    d_assert(s, return, "Null param");
    d_assert(e, return, "Null param");

    mme_sm_trace(3, e);

    switch (event_get(e))
    {
        case FSM_ENTRY_SIG:
        {
            break;
        }
        case FSM_EXIT_SIG:
        {
            break;
        }
        default:
        {
            d_error("Unknown event %s", mme_event_get_name(e));
            break;
        }
    }
}

