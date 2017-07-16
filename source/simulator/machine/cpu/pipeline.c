//
// Created by hsart on 10/07/17.
//

#include "types.h"
#include "structures/fifo.h"

void pipe_fetch(CPU *cpu) {

    cpu->pipeline.ri = mem_read_word(cpu->cache.mem, cpu->pipeline.pc.decimal);
    cpu->pipeline.pc.decimal += WORD_SIZE;

}

void pipe_decode(CPU *cpu) {

    Opcode opcode = { .opcode = cpu->pipeline.ri.decimal };
    void (*realization)(CPU *, unsigned int);
    EType type = TYPE_UNKNOWN;

    size_t m = 0, n = 0;
    if      (opcode.r.op == 0x00) { m = COLUMN_FUNCT1; type = TYPE_R; }
    else if (opcode.r.op == 0x1c) { m = COLUMN_FUNCT2; type = TYPE_R; }
    else if (opcode.r.op == 0x01) { m = COLUMN_RT; type = TYPE_RI; }

    if      (m == COLUMN_FUNCT1 || m == COLUMN_FUNCT2) n = opcode.r.func;
    else if (m == COLUMN_RT)                           n = opcode.r.rt;
    else                                               n = opcode.r.op;

    realization = cpu->inst_set.table[m][n];
    fifo_add(&cpu->pipeline.queue, opcode, type, realization);
    fifo_print(&cpu->pipeline.queue);
    //instruction(cpu, cpu->pipeline.ri.decimal);

}

void pipe_emition(CPU *cpu) {

}

void pipe_exec(CPU *cpu, unsigned int code) {

}

void pipe_mem_access(CPU *cpu, unsigned int code) {

}

void pipe_write_back(CPU *cpu, unsigned int code) {

}


Pipeline pipe_init() {
    Pipeline pipeline = { .pc = {0}, .ri = {0}, .queue = fifo_init(),
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[EXEC]        = &pipe_exec,
            .stage[MEM_ACCESS]  = &pipe_mem_access,
            .stage[WRITE_BACK]  = &pipe_write_back};
    return pipeline;
}
