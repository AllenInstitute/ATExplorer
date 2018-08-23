#ifndef atExplorerAppMessagesH
#define atExplorerAppMessagesH
#include <string>
#define FINISHED_RENDER_ROTATE     (WM_USER + 0x0100)

using std::string;
struct TextMessage
{
	Cardinal Msg;
    int wparam;
    string lparam;
    LRESULT Result;
};
#endif

//#include "atVolumeCreatorMessages.h"
