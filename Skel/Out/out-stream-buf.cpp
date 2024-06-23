//  self

    #include "out-stream-buf.h"



int OutStreamBuf :: overflow (int chr)
{
    switch (chr)
    {
        default:
            Buffer += char (chr);
            break;

        case '\n':
            {
                emit sigOut (QString::fromStdString (Buffer));
                Buffer.clear();
            }
            break;

        case '\r':
            break;
    }

    return chr;
}
