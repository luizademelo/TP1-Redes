# detalhes 
- Servidor e Cliente devem estar em arquivos separados.
- O trabalho deve ser entregue utilizando a linguagem C (Não é permitido o
uso de C++).
- O mesmo deverá ser desenvolvido para máquinas Linux (Não utilizem
bibliotecas que não sejam compatíveis).
- Todas as linhas do código que remetem à conexão devem ser comentadas
explicando sua função.
- Os alunos devem implementar um mecanismo de comunicação adequado
entre os clientes e o servidor, como sockets TCP/IP.
- Deve ser utilizado IPv4 e IPv6. Desta forma, o servidor deve ser configurado
com o parâmetro que define o tipo de IP. O segundo parâmetro deverá ser a
porta utilizada. Exemplo:
  - $ ./server ipv4 50501
  - $ ./server ipv6 50501
- O cliente também deverá receber parâmetros. Primeiro a versão do IP (ipv4
ou ipv6), em seguida o IP do servidor e por fim a porta. Exemplo:
  - $ ./client ipv4 127.0.0.1 50501
  - $ ./client ipv6 ::1 50501
