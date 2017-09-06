#ifndef __MME_S11_HANDLER_H__
#define __MME_S11_HANDLER_H__

#include "gtp_message.h"

#include "mme_context.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

CORE_DECLARE(void) mme_s11_handle_create_session_request(mme_sess_t *sess);
CORE_DECLARE(void) mme_s11_handle_create_session_response(
        gtp_xact_t *xact, mme_bearer_t *bearer,
        gtp_create_session_response_t *rsp);
CORE_DECLARE(void) mme_s11_handle_modify_bearer_response(
        gtp_xact_t *xact, mme_ue_t *mme_ue, gtp_modify_bearer_response_t *rsp);
CORE_DECLARE(void) mme_s11_handle_delete_all_sessions_in_ue(mme_ue_t *mme_ue);
CORE_DECLARE(void) mme_s11_handle_delete_session_response(
        gtp_xact_t *xact, mme_ue_t *mme_ue, gtp_delete_session_response_t *rsp);
CORE_DECLARE(void) mme_s11_handle_create_bearer_request(
        gtp_xact_t *xact, mme_ue_t *mme_ue, gtp_create_bearer_request_t *rsp);

CORE_DECLARE(void) mme_s11_handle_release_access_bearers_response(
        gtp_xact_t *xact, mme_ue_t *mme_ue,
        gtp_release_access_bearers_response_t *rsp);
CORE_DECLARE(void) mme_s11_handle_downlink_data_notification(
        gtp_xact_t *xact, mme_ue_t *mme_ue,
        gtp_downlink_data_notification_t *noti);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MME_S11_HANDLER_H__ */
