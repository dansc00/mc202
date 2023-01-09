###############################################################################################
# Originaly written by Welverton Rodrigues da Silva.
# Last modified by Elisa Dell'Arriva, in 2021/04/04.
###############################################################################################


###############################################################################################
# INSTRUÇÕES DE USO
# make
#			compila o código utilizando todos os arquivos .c que estiverem na mesma pasta em que
#			estiver o arquivo Makefile.
#
# make testar
#			roda o cppcheck em todos os arquivos .c que estiverem na mesma pasta em que estiver o
#			arquivo Makefile e, em seguida, checa se a resposta gerada para os testes (arquivos.in)
#			que estiverem dentro da pasta 'testes' estão de acordo com as respostas esperadas
#			(arquivos .res), os quais também devem estar dentro da pasta 'testes'.
#
# make checar
#			confere se há problemas de alocação de memória no código.
###############################################################################################


###############################################################################################
######################### Compilação com suporte a múltiplos arquivos #########################
###############################################################################################

.PHONY: build clean

LAB = lab

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
GFLAGS  = -std=c99 -Wall -Werror

build: $(OBJECTS)
	gcc $(GFLAGS) *.o -o $(LAB) -lm

%.o: %.c
	gcc $(GFLAGS) -g -c $< -o $@

clean:
	rm -f *.o


###############################################################################################
####################### Suporte para testar o programa usando os testes #######################
###############################################################################################

.PHONY: testar

testar:
	@set -e ; \
	if [ ! -d testes ] ; then \
		echo "\033[1;31mDiretório 'testes' não encontrado!\033[0m" ; \
		exit 1 ; \
	fi ; \
	echo "\033[1;34mRodando cppcheck:\033[0m" ;\
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c99  *.c ;\
	for entrada in testes/*.in ; do \
		echo "\033[1;34mTestando \033[4;34m$$entrada\033[0m" ; \
		saida=$$(echo "$$entrada" | sed -re 's/\.in$$/.out/' ) ; \
		resposta=$$(echo "$$entrada" | sed -re 's/\.in$$/.res/' ) ; \
		./$(LAB) < "$$entrada" > "$$saida" ; \
		if diff "$$resposta" "$$saida" ;  then \
			echo "\033[1;32mResultado correto!\033[0m" ; \
		else \
			echo "\033[1;31mFalhou!\033[0m" ; \
			exit 1; \
		fi ; \
		echo ; \
	done

###############################################################################################
###################### Suporte para checar o programa usando o valgrind #######################
###############################################################################################

.PHONY: checar

checar:
	@set -e ; \
	if [ ! -d testes ] ; then \
		echo "\033[1;31mDiretório 'testes' não encontrado!\033[0m" ; \
		exit 1 ; \
	fi ; \
	for entrada in testes/*.in ; do \
		echo "\033[1;34mChecando \033[4;34m$$entrada\033[0m" ; \
		saida=$$(echo "$$entrada" | sed -re 's/\.in$$/.out/' ) ; \
		resposta=$$(echo "$$entrada" | sed -re 's/\.in$$/.res/' ) ; \
		if valgrind -q --leak-check=full ./$(LAB) < "$$entrada" > "$$saida" ;  then \
			echo "\033[1;32mResultado correto!\033[0m" ; \
		else \
			echo "\033[1;31mFalhou! Tem problemas de memória.\033[0m" ; \
			exit 1; \
		fi ; \
		echo ; \
	done
