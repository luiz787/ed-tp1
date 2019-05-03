#include <iostream>
#include "Curso.hpp"
#include "ListaException.hpp"

static const uint8_t PRIMEIRA_OPCAO = 1;
static const uint8_t SEGUNDA_OPCAO = 2;

void lerEntrada(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void processar(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void imprimirResultado(Lista<Curso> &cursos);

Curso* obterCursoPorId(Lista<Curso> &cursos, uint16_t id);

Lista<Aluno> filtrarAlunosPossuemEsperancaAprovacao(Lista<Aluno> &alunos);
Lista<Aluno> filtrarAlunosNaoAprovadosPrimeiraOpcao(Lista<Aluno> &alunos);

void popularListasIntermediarias(Lista<Curso> &cursos, Lista<Aluno> &alunos, uint8_t opcao);
void popularListasIntermediariasPrimeiraOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void popularListasIntermediariasSegundaOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void processarListasIntermediarias(Lista<Curso> &cursos);

void atribuirListasDeEspera(Lista<Curso> &cursos, const Lista<Aluno> &alunosNaoAprovadosPrimeiraOpcao);
void consolidarAprovados(const Lista<Curso> &cursos);

int main() {
    try {
        Lista<Curso> cursos;
        Lista<Aluno> alunos;
        lerEntrada(cursos, alunos);
        processar(cursos, alunos);
        imprimirResultado(cursos);
    } catch (ListaException& e) {
        std::cout << e.what();
    }
    return 0;
}

void lerEntrada(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    uint16_t n, m;
    std::cin >> n >> m;
    for (uint16_t i = 0; i < n; i++) {
        std::string nomeCurso;
        std::cin.ignore();
        std::getline(std::cin, nomeCurso);
        uint16_t quantidadeVagas;
        std::cin >> quantidadeVagas;
        cursos.adicionarNoFinal(new Curso(i, nomeCurso, quantidadeVagas));
    }
    for (uint16_t i = 0; i < m; i++) {
        std::string nomeAluno;
        std::cin.ignore();
        std::getline(std::cin, nomeAluno);
        double nota;
        uint16_t idCursoPrimeiraOpcao, idCursoSegundaOpcao;
        std::cin >> nota >> idCursoPrimeiraOpcao >> idCursoSegundaOpcao;
        alunos.adicionarNoFinal(new Aluno(i, nomeAluno, nota, idCursoPrimeiraOpcao, idCursoSegundaOpcao));
    }
}

void processar(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    auto alunosPossuemEsperancaAprovacao = alunos;
    uint8_t opcaoAtual = PRIMEIRA_OPCAO;
    while (!alunosPossuemEsperancaAprovacao.vazia()) {
        popularListasIntermediarias(cursos, alunosPossuemEsperancaAprovacao, opcaoAtual);
        processarListasIntermediarias(cursos);
        alunosPossuemEsperancaAprovacao = filtrarAlunosPossuemEsperancaAprovacao(alunos);
        opcaoAtual = SEGUNDA_OPCAO;
    }
    atribuirListasDeEspera(cursos, filtrarAlunosNaoAprovadosPrimeiraOpcao(alunos));
    consolidarAprovados(cursos);
}

void popularListasIntermediarias(Lista<Curso> &cursos, Lista<Aluno> &alunos, uint8_t opcao) {
    if (opcao == 1) {
        popularListasIntermediariasPrimeiraOpcao(cursos, alunos);
    } else if (opcao == 2) {
        popularListasIntermediariasSegundaOpcao(cursos, alunos);
    }
}

void popularListasIntermediariasPrimeiraOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    auto nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        auto cursoPrimeiraOpcao = obterCursoPorId(cursos, aluno->getCodigoPrimeiraOpcao());
        cursoPrimeiraOpcao->adicionarAlunoListaIntermediaria(aluno);
        nodeAluno = nodeAluno->getProximo();
    }
}

void popularListasIntermediariasSegundaOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    auto nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        auto cursoSegundaOpcao = obterCursoPorId(cursos, aluno->getCodigoSegundaOpcao());
        cursoSegundaOpcao->adicionarAlunoListaIntermediaria(aluno);
        nodeAluno = nodeAluno->getProximo();
    }
}

void processarListasIntermediarias(Lista<Curso> &cursos) {
    auto nodeCurso = cursos.getPrimeiro();
    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        curso->processarListaIntermediaria();
        nodeCurso = nodeCurso->getProximo();
    }
}

void atribuirListasDeEspera(Lista<Curso> &cursos, const Lista<Aluno> &alunosNaoAprovadosPrimeiraOpcao) {
    auto nodeAluno = alunosNaoAprovadosPrimeiraOpcao.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        auto cursoPrimeiraOpcao = obterCursoPorId(cursos, aluno->getCodigoPrimeiraOpcao());
        cursoPrimeiraOpcao->adicionarAlunoListaEspera(aluno);
        if (!aluno->isAprovadoSegundaOpcao()) {
            auto cursoSegundaOpcao = obterCursoPorId(cursos, aluno->getCodigoSegundaOpcao());
            cursoSegundaOpcao->adicionarAlunoListaEspera(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
}

void consolidarAprovados(const Lista<Curso> &cursos) {
    auto nodeCurso = cursos.getPrimeiro();
    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        curso->consolidarListaAprovados();
        nodeCurso = nodeCurso->getProximo();
    }
}

Lista<Aluno> filtrarAlunosNaoAprovadosPrimeiraOpcao(Lista<Aluno> &alunos) {
    auto alunosNaoAprovadosPrimeiraOpcao = Lista<Aluno>();

    auto nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (!aluno->isAprovadoPrimeiraOpcao()) {
            alunosNaoAprovadosPrimeiraOpcao.adicionarNoFinal(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
    return alunosNaoAprovadosPrimeiraOpcao;
}

Lista<Aluno> filtrarAlunosPossuemEsperancaAprovacao(Lista<Aluno> &alunos) {
    auto alunosPossuemEsperancaAprovacao = Lista<Aluno>();

    auto nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (aluno->possuiEsperancaAprovacao()) {
            alunosPossuemEsperancaAprovacao.adicionarNoFinal(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
    return alunosPossuemEsperancaAprovacao;
}

Curso* obterCursoPorId(Lista<Curso> &cursos, uint16_t id){
    auto curso = cursos.getPrimeiro();
    while (curso != nullptr) {
        if (curso->getValor()->getId() == id) {
            return curso->getValor();
        } else {
            curso = curso->getProximo();
        }
    }
    throw ListaException("Curso requisitado não está na lista de cursos.");
}

void imprimirResultado(Lista<Curso> &cursos) {
    auto noCurso = cursos.getPrimeiro();
    while(noCurso != nullptr) {
        std::cout << *noCurso->getValor();
        if (noCurso->getProximo() != nullptr) {
            std::cout << std::endl;
        }
        noCurso = noCurso->getProximo();
    }
}
