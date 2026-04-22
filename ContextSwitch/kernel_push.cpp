// 슬라이드 11: P0에서 나갈 때 (이미 배운 내용)
// CPU가 자동으로: push SS, RSP, RFLAGS, CS, RIP → 커널 스택
// OS가 직접:     PCB₀.rax = RAX; PCB₀.rbx = RBX; ...
// OS가 이동:     PCB₀.rip = 커널스택.pop();  // 나중에 쓰려고 PCB로 옮김

// ─────── 스케줄러가 P1 선택 ───────

// P1으로 복원 (대칭 구조)
void restore_context(PCB* pcb1) {
    // 1단계: 범용 레지스터는 mov로 바로 복원 가능
    RAX = pcb1->rax;
    RBX = pcb1->rbx;
    // ... 나머지 범용 레지스터
    
    // 2단계: RIP/RSP/RFLAGS는 mov로 못 바꿈 → 커널 스택에 "예약"
    kernel_stack_push(pcb1->ss);
    kernel_stack_push(pcb1->rsp);
    kernel_stack_push(pcb1->rflags);
    kernel_stack_push(pcb1->cs);
    kernel_stack_push(pcb1->rip);
    
    // 3단계: iret 명령 실행
    //   → CPU가 스택을 pop하면서 원자적으로:
    //     RIP, CS, RFLAGS, RSP, SS를 한 번에 복원하고
    //     복원된 RIP 주소로 점프 → P1 실행 재개!
    asm("iret");
}
