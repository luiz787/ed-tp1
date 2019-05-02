#include <iostream>
#include "Curso.hpp"
#include "ListaException.hpp"

void lerEntrada(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void processar(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void imprimirResultado(Lista<Curso> &cursos);
Curso* obterCursoPorId(Lista<Curso> &cursos, uint16_t id);
Lista<Aluno> filtrarAlunosNaoAprovadosPrimeiraOpcao(Lista<Aluno> &alunos);
Lista<Aluno> filtrarAlunosRejeitados(Lista<Aluno> &alunos);
void popularListasIntermediariasPrimeiraOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void popularListasIntermediariasSegundaOpcao(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void consolidarAprovados(const Lista<Curso> &cursos);

void atribuirListasDeEspera(Lista<Curso> &cursos, const Lista<Aluno> &alunosNaoAprovadosPrimeiraOpcao);

void processarListasIntermediarias(Lista<Curso> &cursos);

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
    // alunos.ordenar();
    popularListasIntermediariasPrimeiraOpcao(cursos, alunos);
    processarListasIntermediarias(cursos);

    Lista<Aluno> alunosNaoAprovadosPrimeiraOpcao = filtrarAlunosNaoAprovadosPrimeiraOpcao(alunos);
    popularListasIntermediariasSegundaOpcao(cursos, alunosNaoAprovadosPrimeiraOpcao);
    processarListasIntermediarias(cursos);

    Lista<Aluno> alunosRejeitados = filtrarAlunosRejeitados(alunos);
    popularListasIntermediariasSegundaOpcao(cursos, alunosRejeitados);
    processarListasIntermediarias(cursos);

    atribuirListasDeEspera(cursos, filtrarAlunosNaoAprovadosPrimeiraOpcao(alunos));

    consolidarAprovados(cursos);
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

Lista<Aluno> filtrarAlunosRejeitados(Lista<Aluno> &alunos) {
    auto alunosRejeitados = Lista<Aluno>();

    auto nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (aluno->isRejeitado()) {
            alunosRejeitados.adicionarNoFinal(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
    return alunosRejeitados;
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
