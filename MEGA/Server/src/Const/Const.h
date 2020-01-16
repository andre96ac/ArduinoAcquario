#ifndef CONST_H
#define CONST_H

#define ACCESO 1
#define SPENTO 0
#define NMAXPARAMS 30
#define NMAXLED 10
#define NDIGITALPIN 14
#define NANALOGPIN 6
#define NMAXCONTROLLERS 5
#define PORT 80

const int CONFIGJSONSIZE=(
                            JSON_OBJECT_SIZE(4)
                            +2*JSON_ARRAY_SIZE(NMAXCONTROLLERS)
                            +JSON_ARRAY_SIZE(NMAXLED)
                            +NMAXLED*JSON_OBJECT_SIZE(3)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(5)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                        );


#endif
