//
// Created by hsart on 10/07/17.
//

#include "../types.h"
#include "cpu.h"


void pipe_fetch(CPU *cpu) {
    cpu->pipeline.ri = cpu->cache.mem->byte[cpu->pipeline.pc];
    cpu->pipeline.pc += WORD_SIZE;
}
void pipe_decode(CPU *cpu) {





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
