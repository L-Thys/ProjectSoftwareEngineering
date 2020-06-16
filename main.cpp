//
// this file is only used for the PSE executable
//

#include "library.h"
#include "Metronet.h"

int main(){
    Metronet* metronet = readFromXml("test.xml");
    metronet->isConsistent();
    delete metronet;
    return 0;
}
