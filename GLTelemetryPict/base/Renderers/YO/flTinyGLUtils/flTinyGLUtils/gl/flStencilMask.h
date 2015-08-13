//
//  StencilMask.h
//  test
//
//  Created by Onishi Yoshito on 6/24/13.
//
//

#ifndef __test__StencilMask__
#define __test__StencilMask__

#include <OpenGL/gl.h>

namespace fl {
    
    class StencilMask {
    public:
        enum Op {
            OP_POSITIVE = 0,
            OP_NEGATIVE = 1,
        };
        
        StencilMask();
        virtual ~StencilMask();
        
        // clear stencil buffer
        void clear();
        
        void begin();
        // create a mask between those methods
        // like:
        // stencil.begin();
        // drawCircle(center, radius);
        // stencil.end();
        void end();
        
        void bind();
        // use mask between those methods
        // like:
        // stencil.bind();
        // drawMyScene();
        // stencil.unbind();
        void unbind();
        
        // set mask operation
        // like:
        // setOpe(StencilMask::OP_POSITIVE);
        void setOp(Op op);
        
    private:
        GLuint mOp;
    };
    
}

#endif /* defined(__test__StencilMask__) */
