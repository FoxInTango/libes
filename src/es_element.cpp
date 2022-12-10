#include "es_element.h"
#include "es_context.h"
#include <vector>
#include <map>

/**
 * objects:
 *     var obj = {} | "" | 2000 | ["","",{}];
 *     let obj = same as var;
 * expressions:
 *     obj.member1,member2,member3
 *     obj = a + b * (c + d);
 * switch:
 *     
 *     
 */
typedef std::vector<es_element*> ES_element_array;
class es_element_implement{
public:
    es_element*         owner;
    es_context*         context;
    //es_prototype        prototype;
    ES_element_array    subelements;
public:
    es_element_implement(){

    }

    ~es_element_implement(){
    
    }
};

class es_element_string      :public es_element_implement{};
class es_element_number      :public es_element_implement{};
class es_element_array       :public es_element_implement{};
class es_element_object      :public es_element_implement{};
class es_element_function    :public es_element_implement{};
class es_element_scope       :public es_element_implement{};
class es_element_return      :public es_element_implement{};/** jump to highter level*/
class es_element_switch      :public es_element_implement{};/** if | switch */
class es_element_loop        :public es_element_implement{};
