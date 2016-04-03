pilha   segment stack
        db      8192    dup(0)
pilha   ends

dados   segment

NL      equ     0dh      ;"enter"
BS      equ     08h      ;back space

Nova_lin db NL,0ah,00h   ;nova linha

;-----Mensagens apresentadas na tela---------
le_dia 	db	'Digite o dia: ',0    
le_mes 	db 	'Digite o mes: ',0
le_ano 	db 	'Digite o ano: ',0

inv_dia	db 	'Dia invalido',0
inv_mes	db 	'Mes invalido',0
inv_ano	db 	'Ano invalido',0

text_fin1 db    0dh, 0ah, 'O dia ',0     ;Imprime a frase: 'O dia "dia" de "mes" 
text_fin2 db    ' de ',0         ;          de "ano" eh um(a) "dia_de_semana" '
text_fin3 db    ' eh um(a) ',0dh, 0ah, 0   ;

;-------Meses do Ano--------------------------
jan     db      'JANEIRO',0
fev     db      'FEVEREIRO',0
mar     db      'MARCO',0
abr     db      'ABRIL',0
mai     db      'MAIO',0
jun     db      'JUNHO',0
jul     db      'JULHO',0
ago     db      'AGOSTO',0
set     db      'SETEMBRO',0
otb     db      'OUTUBRO',0
nov     db      'NOVEMBRO',0
dez     db      'DEZEMBRO',0

nome_meses      dw      jan, fev, mar, abr, mai, jun, jul, ago, set, otb, nov, dez

;-------Dias da Semana-----------------------
dom     db      'DOMINGO',0
sgd     db      'SEGUNDA',0
ter     db 	'TERCA',0
qua	db	'QUARTA',0
qui	db	'QUINTA',0
sex	db	'SEXTA',0
sab	db	'SABADO',0

nome_dia        dw      dom, sgd, ter, qua, qui, sex, sab

tam_meses       db      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31

bufD     db      10 dup (?)   ; buffer que armazena o dia
bufM     db      10 dup (?)   ; buffer que armazena o mes
bufA     db      10 dup (?)   ; buffer que armazena o ano

ANO     dw 0   ;armazena o ano apos ser decomposto de ascii para decimal
DIA     dw 0   ;armazena o dia apos ser decomposto de ascii para decimal
MES     db 0   ;armazena numero do mes 

DIA1_1_1900     equ     1       ; 1 de janeiro de 1900 foi segunda-feira

DIA_REF         equ     1
MES_REF         equ     1
ANO_REF         equ     1900

anos_dec        dw      0       ; qtd. de anos desde o ano-referencia
meses_dec       db      0       ; qtd. de meses desde o mes-referencia
dias_dec        dw      0       ; qtd. de dias desde o dia-referencia

num_biss        dw      0       ; qtd. de anos bissextos no periodo

total           dw      0       ; qtd. de meses decorridos, em dias
        

dados   ends

codigo  segment
        assume  cs:codigo, ds:dados, ss:pilha, es:dados

inicio:
        mov     ax, dados
        mov     ds, ax
        mov     es, ax
      	
;---Leitura do dia--------
	lea 	si,le_dia
  	call 	puts     
  	mov 	cx,3
  	lea	di, bufD
  	call 	gets

	push 	cx
  	push 	di

	lea	si,Nova_lin
	call	puts
      	
;---Leitura do mes--------
  	lea	si,le_mes
  	call	puts
  	mov	cx,10
  	lea	di, bufM
  	call	gets

	push 	cx
  	push 	di
  
  	lea  	si,Nova_lin      ;Nova linha
  	call	puts
        
;---Leitura do ano--------
  	lea	si,le_ano    
  	call 	puts
  	mov 	cx,5 
  	lea	di, bufA
  	call 	gets
	
	call 	ver_ano    ;valida o ano
        or      cx, cx
        jz      ano_valido
  	mov	cx,1
        jmp     not_valid

ano_valido:

	pop 	di
	pop 	cx
	call	ver_mes    ;valida o mes
        cmp     cx,-1
        jne     mes_valido
	mov	cx,2
        jmp     not_valid
mes_valido:
        mov     MES, cl         ; ch eh retornado, mas nao eh importante
	pop	di
	pop	cx
	call	ver_dia   ;valida o dia

        or      cx, cx
        jz      dia_valido
        mov     cx, 3

not_valid:
 	lea  	si,Nova_lin      ;Nova linha
  	call	puts

	call	invalid
        jmp     fim_prog


dia_valido:

;------------------------------------------------------------------------
; secao de calculos e mais calculos (--> oo )
;------------------------------------------------------------------------

; calcula anos_dec = ANO-ANO_REF
        mov     ax, ANO
        sub     ax, ANO_REF
        mov     anos_dec, ax

; calcula dias_dec = DIA-DIA_REF
        mov     ax, DIA
        sub     ax, DIA_REF
        mov     dias_dec, ax

; calcula meses_dec = MES-MES_REF
        mov     al, MES
        sub     al, MES_REF
        inc     al
        mov     meses_dec, al


; calcula num_biss (divide (anos_dec-1) por 4
        mov     ax, anos_dec
        cmp     ax, 0
        je      sem_biss
        dec     ax
        mov     cl, 2
        shr     ax, cl
        mov     num_biss, ax
sem_biss:

; calcula numero de dias decorridos, do inicio do ano ateh
;   o inicio do mes atual

        lea     si, tam_meses                        
        mov     cl, meses_dec
        xor     ch, ch
        xor     dx, dx
        xor     ah, ah
        cmp     meses_dec, 0
        je      depois_laco

laco_total:
        lodsb
        add     dx, ax
        loop    laco_total

depois_laco:

; se ano for bissexto, e mes for maior que fevereiro, soma 1 ao total
        cmp     MES, 1
        jbe     continua_princ
        call    bissexto
        or      cx, cx
        jnz     continua_princ
        inc     dx

continua_princ:
        add     dx, dias_dec
        mov     total, dx

; calcula quando foi o dia 1 de janeiro do ano escolhido

        mov     ax, anos_dec
        add     ax, num_biss
        add     ax, DIA1_1_1900

        mov     cl, 7
        div     cl

        mov     dx, total
        xor     al, al
        xchg    ah, al
        add     ax, dx

; agora divide numero obtido por 7 (resto eh dia da semana)
        mov     cl, 7
        div     cl
; dia da semana (0=domingo) em AH

        lea     si, text_fin1
        call    puts
        lea     si, bufD
        call    puts
        lea     si, text_fin2
        call    puts
        lea     si, bufM
        call    puts
        lea     si, text_fin2
        call    puts
        lea     si, bufA
        call    puts
        lea     si, text_fin3
        call    puts


        lea     bx, nome_dia
        xor     al, al
        xchg    ah, al

        shl     ax, 1

        add     bx, ax
        mov     si, [bx]
        call    puts
        lea     si, Nova_lin
        call    puts

        jmp     fim_prog


fim_prog:
        mov     ah, 4ch
        int     21h

; entrada: si=src, di=dst
; saida: ax.. 0 se iguais, -1 se diferentes
strcmp  proc    near
        push    si
        push    di
cmp_laco:
        lodsb
        cmp     al,[di]
        jne     fim_dif
        or      al, al
        jz      fim_eq
        inc     di
        jmp     cmp_laco
fim_dif:
        xor     ax,ax
        dec     ax
        jmp     fim_cmp

fim_eq:
        xor     ax,ax

fim_cmp:
        pop     di
        pop     si
        ret
strcmp  endp

;puts - imprime um string ASCIIZ
; entrada: string em DS:SI

puts    proc    near
        push    ax
        push    dx
        push    si

        mov     ah, 2
laco:
        lodsb
        or      al, al
        jz      fim_puts
        mov     dl, al
        int     21h
        jmp     laco
fim_puts:
        pop     si
        pop     dx
        pop     ax
        ret
puts    endp

; le um caractere do teclado
; saida: al = caractere; destroi AH

getch   proc    near
        mov     ah, 07
        int     21h
        ret
getch   endp

; imprime um caractere na tela
; entrada: al = caractere
putch   proc    near
        push    ax
        push    dx
        mov     dl, al
        mov     ah, 2
        int     21h
        pop     dx
        pop     ax
        ret
putch   endp

; le uma string do teclado
; entrada: cx: tamanho maximo do string (-1)
;          es:di - endereco do buffer de destino
; saida:   cx: numero de caracteres lidos
;          es:di - string lida (ASCIIZ)

gets    proc    near
        push    ax
        push    bx
        push    dx
        push    di

        xor     bx, bx

laco_gets:
        call    getch
; se for enter, fim da leitura
        cmp     al, NL
        je      fim_gets
; se nao for backspace, poe no buffer
        cmp     al, BS
        je      gets_bs

        stosb   ; poe caractere em es:di, incrementa di

        call    putch   ; apresenta caractere na tela
        inc     bx      ; incrementa contador de caracteres lidos
; se qtd. de caracteres lidos = maximo, fim da leitura
        cmp     bx, cx
        je      fim_gets;

        jmp     laco_gets
;---- tratamento de BackSpace ----
gets_bs:
        or      bx, bx
        jz      laco_gets       ; se nao tiver nada no buffer, repete laco

        call    putch           ; imprime BS
        mov     al, ' '         
        call    putch           ; imprime espaco
        mov     al, BS
        call    putch           ; imprime BS denovo

        dec     di              ; elimina um caractere do buffer
        dec     bx              ; e desconta no nr. de caracteres lidos

        jmp     laco_gets

;---- fim da leitura ----
fim_gets:
        xor     al, al          ; armazena terminador de string
        stosb                   ; no buffer

        mov     cx, bx          ; nr. de caracteres retorna em CX

        pop     di
        pop     dx
        pop     bx
        pop     ax
        ret
gets    endp

;Imprime mensagem inválida
;entrada: cx: onde foi o erro (1-ano,2-mes,3-dia)
;saida  : mensagem na tela
invalid proc near

	cmp	cx,3
	jne	test_mes
        lea     si,inv_dia
	call	puts
	jmp	end_inv
test_mes:
	cmp	cx,2
        jne     test_ano
	lea	si,inv_mes
	call	puts
	jmp	end_inv
test_ano:
	cmp	cx,1
	jne	end_inv
        lea     si,inv_ano
	call	puts
end_inv:
	ret

invalid endp

;ver_ano - valida o ano
; entrada: string do ano em es:di
;          cx: tamanho do ano
; saída  :  Se ano OK:
;                     cx: 0 
;                     ANO: ano lido
;           Senão:
;                 cx: -1
;                 ANO: 0               
ver_ano proc near
	push	bx
	push	ax
	push	si

	mov 	si,di

contano:
	lodsb
        cmp     al, '0'
        jb      ano_inval
        cmp     al, '9'
        ja      ano_inval

        sub     al,'0'

        push    ax
        push    cx
        mov     cl, 10
        mov     ax, ANO
        mul     cl
        mov     bx, ax
        pop     cx
        pop     ax
        xor     ah, ah
        add     bx, ax
        mov     ANO, bx
        loop    contano

        cmp     ANO, 1900
        jb      ano_inval
        cmp     ANO, 2100
        ja      ano_inval

        xor     cx, cx
        jmp     fim_ver_ano

ano_inval:
        mov	cx,-1      ; -1 se o ano for inválido

fim_ver_ano:
        pop     bx
        pop     ax
        pop     si
        ret 
ver_ano endp

;valida mes
; entrada:  di: mes lido
; saída:    cx: -1 se invalido,
;           cx: numero do mes se ok
ver_mes proc near

	xor	dx, dx
        mov     cx, 12
        lea     bx, nome_meses
laco_mes:
	mov	si, [bx]
	call	strcmp
        or      ax, ax
        jz      fim_cmp_mes
	add	bx, 2	
	inc	dx
        loop    laco_mes
        jmp     not_found

fim_cmp_mes:
	mov	cx, dx
	jmp	mes_fim

not_found:
	mov	cx, -1

mes_fim:
	ret
ver_mes endp

;valida dia
; entrada: cx    : tamanho do dia lido
;	   ds:di : dia lido
; usa: MES
; saida:   DIA: numero do dia
;          cx = 0 se ok, -1 se erro
ver_dia proc near
	push	bx
	push	ax
	push	si

	mov 	si,di

contn:
	lodsb
        cmp     al, '0'
        jb      inval
        cmp     al, '9'
        ja      inval

        sub     al,'0'

        push    ax
        push    cx
        mov     cl, 10
        mov     ax, DIA
        mul     cl
        mov     bx, ax
        pop     cx
        pop     ax
        xor     ah, ah
        add     bx, ax
        mov     DIA, bx
        loop    contn

        mov     al, MES
        cmp     al, 1
        jne     testa_normal

        mov     ax, DIA
        cmp     ax, 29
        jb      testa_normal
        ja      inval
        call    bissexto
        or      cx, cx
        jnz     inval
        jmp     dia_ok

testa_normal:
        lea     bx, tam_meses
        mov     al, MES
        xlat
        cbw
        mov     bx, DIA
        cmp     bx, ax
        ja      inval
dia_ok:
        xor     cx, cx
        jmp     fim_dia

inval:
        xor     cx, cx
        dec     cx

fim_dia:
	pop	si
	pop	ax
	pop	bx	
	ret
ver_dia endp

;verifica se ano eh bissexto
; entrada: ANO: ano jah decomposto
; saída: cx: 0 - se eh bissexto
;  	 cx: -1 - se nao eh bissexto
bissexto proc near
	push	ax
	push	bx
	push	dx

        xor     dx, dx
	mov	ax,ANO
	mov	bx,4
	div	bx      ;divide por 4 e resto em dx
	cmp	dx,0
	je	eh_bi
	
	xor 	cx,cx
	dec 	cx
	jmp	f_im
eh_bi:
	xor	cx,cx
f_im:	
	pop	dx
	pop	bx
	pop	ax
	ret
bissexto endp


codigo  ends

        end inicio
        


