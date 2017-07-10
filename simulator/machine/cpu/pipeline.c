//
// Created by hsart on 10/07/17.
//

#include "types.h"

struct dec_code {
    int opcode : 6;
    int funct : 6;
};

void pipe_fetch(CPU *cpu, unsigned int code) {
    cpu->pipeline.ri =
    cpu->pipeline.pc += 4;
}
void pipe_decode(CPU *cpu, unsigned int code) {

    EInstructions inst;
    struct dec_code dec = { .opcode = code };

    if (code == 0) {

    }


}
void pipe_exec(CPU *cpu, unsigned int code) {

}
void pipe_mem_access(CPU *cpu, unsigned int code) {

}
void pipe_write_back(CPU *cpu, unsigned int code) {

}

Pipeline pipe_init() {
    Pipeline pipeline = { .pc = 0,
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[EXEC]        = &pipe_exec,
            .stage[MEM_ACCESS]  = &pipe_mem_access,
            .stage[WRITE_BACK]  = &pipe_write_back};
    return pipeline;
}
