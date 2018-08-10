#ifndef atExplorerAppMessagesH
#define atExplorerAppMessagesH

#define FINISHED_RENDER_ROTATE     (WM_USER + 0x0100)

struct TextMessage
{
	Cardinal Msg;
    int wparam;
    string lparam;
    LRESULT Result;
};
#endif

//#include "atVolumeCreatorMessages.h"
