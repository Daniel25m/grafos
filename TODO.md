# TG1 - Rede Social em Grafos

Projeto 1 de Teoria dos Grafos - Turma 6N  
Universidade Presbiteriana Mackenzie, 2026

## Integrantes

- Daniel Monteiro Malacarne - 10420454
- Murillo Henrique Sakamoto - 10426242

**Entrega:** até 18:00 de 28 de setembro, no Moodle  
**Formato:** um único `.zip` contendo o PDF da modelagem e um arquivo `.c` em ANSI C

## 1. Definições iniciais

### Grupo social e modelagem

- [x] Escolher o grupo social concreto: turma, clube, empresa, elenco de série etc.
- [x] Nomear os 20 usuários.
- [x] Definir os campos de cada vértice: nome, idade, curso etc.
- [x] Definir os campos de cada aresta: tipo de contato, tempo de amizade ou apenas a existência do contato, com justificativa.
- [x] Desenhar o grafo dos 20 usuários garantindo que ele exercite todas as consultas.

### Requisitos do grafo

- [x] Incluir pelo menos um usuário sem nenhum contato.
- [x] Incluir pelo menos um usuário com exatamente um contato.
- [x] Definir claramente o usuário ou os usuários com grau máximo.
- [x] Criar pelo menos duas componentes conexas.
- [x] Gerar as três imagens do documento: `imagem01`, `imagem02` e `grafo-completo`.

## 2. Código em C

- [x] Baixar o `Grafo_2026-2.c` do Moodle e usá-lo como base obrigatória.
- [x] Adaptar as structs para acomodar os dados definidos para vértices e arestas.
- [x] Escrever o cabeçalho com a identificação completa dos dois integrantes.
- [x] Inicializar, no `main`, um único grafo com valor constante contendo toda a rede.

### Funções obrigatórias

- [x] Listar usuários que não contatam ninguém, ou seja, com grau 0.
- [x] Listar usuários que contatam exatamente uma pessoa, ou seja, com grau 1.
- [x] Exibir o usuário ou os usuários com mais contatos.
- [x] Detectar grupos isolados, isto é, componentes conexas.
- [x] Criar uma função para exibir, de forma agradável, todos os detalhes da rede social.
- [x] Documentar o código com comentários úteis.
- [ ] Testar a compilação no Dev-C++ para Windows.

As mensagens exibidas pelo programa devem falar sobre o grupo social. Por
exemplo: `Fulano não conversa com ninguém da turma`, e não: `o vértice 7 tem grau 0`.

## 3. Documento PDF

Arquivo-base: `TG1-rede-social.tex`

- [x] Preencher a seção "O grupo social considerado".
- [x] Preencher a seção "Informações armazenadas em cada vértice".
- [x] Preencher a seção "Informações armazenadas em cada aresta".
- [ ] Escrever a seção de algoritmos de forma muito explicativa, incluindo:
  - [ ] ideia de cada algoritmo;
  - [ ] pseudocódigo;
  - [ ] estrutura de dados utilizada;
  - [ ] complexidade.
- [x] Incluir a seção de resultados com a saída do programa.
- [ ] Listar as fontes consultadas e indicar qual detalhe veio de cada fonte.
- [x] Subir as imagens no Overleaf.
- [ ] Confirmar o nome correto do professor.
- [ ] Revisar a ortografia.
- [ ] Exportar o PDF final.

## 4. Apresentação

- [ ] Preparar uma apresentação de aproximadamente 6 minutos.
- [ ] Garantir a participação dos dois integrantes.
- [ ] Ensaiar a apresentação cronometrando o tempo.

## 5. Entrega

- [ ] Criar um único arquivo `.zip` contendo o PDF e o arquivo `.c`.
- [ ] Publicar o arquivo no Moodle.
- [ ] Confirmar que apenas um dos integrantes precisa realizar a publicação.

## Tarefa adicional para grupos com menos de 3 alunos

O enunciado prevê uma tarefa adicional para grupos com menos de três alunos:
calcular o **índice de proximidade** de cada participante, definido como a média
das distâncias de um vértice até todos os demais.

- [ ] Confirmar com o professor se essa exigência se aplica à dupla.
- [ ] Se for exigida, implementar BFS a partir de cada vértice.
- [ ] Definir o tratamento para vértices em componentes distintas, cuja distância será infinita.
- [ ] Explicar no PDF a fórmula, o algoritmo e o tratamento das distâncias infinitas.
