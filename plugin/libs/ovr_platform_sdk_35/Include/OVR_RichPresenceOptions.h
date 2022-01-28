// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_RICH_PRESENCE_OPTIONS_H
#define OVR_RICH_PRESENCE_OPTIONS_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stddef.h>
#include <stdbool.h>

#include "OVR_RichPresenceExtraContext.h"

struct ovrRichPresenceOptions;
typedef struct ovrRichPresenceOptions* ovrRichPresenceOptionsHandle;

OVRP_PUBLIC_FUNCTION(ovrRichPresenceOptionsHandle) ovr_RichPresenceOptions_Create();
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_Destroy(ovrRichPresenceOptionsHandle handle);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetDestinationApiName
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetApiName(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetArgsString(ovrRichPresenceOptionsHandle handle, const char* key, const char* value);
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_ClearArgs(ovrRichPresenceOptionsHandle handle);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetCurrentCapacity(ovrRichPresenceOptionsHandle handle, unsigned int value);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetLobbySessionId or
/// ovr_GroupPresenceOptions_SetMatchSessionId to specify the session
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetDeeplinkMessageOverride(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetEndTime(ovrRichPresenceOptionsHandle handle, unsigned long long value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetExtraContext(ovrRichPresenceOptionsHandle handle, ovrRichPresenceExtraContext value);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetMatchSessionId
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetInstanceId(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetIsIdle(ovrRichPresenceOptionsHandle handle, bool value);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetIsJoinable
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetIsJoinable(ovrRichPresenceOptionsHandle handle, bool value);
/// DEPRECATED: unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetJoinableId(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetLobbySessionId
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetLobbySessionId(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Use ovr_GroupPresenceOptions_SetMatchSessionId
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetMatchSessionId(ovrRichPresenceOptionsHandle handle, const char * value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetMaxCapacity(ovrRichPresenceOptionsHandle handle, unsigned int value);
/// DEPRECATED: Unused
OVRP_PUBLIC_FUNCTION(void) ovr_RichPresenceOptions_SetStartTime(ovrRichPresenceOptionsHandle handle, unsigned long long value);

#endif
