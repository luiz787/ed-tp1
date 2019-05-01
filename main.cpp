#include <iostream>
#include "Curso.hpp"
#include "ListaException.hpp"

void lerEntrada(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void processar(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void imprimirResultado(Lista<Curso> &cursos);
Curso* obterCursoPorId(Lista<Curso> &cursos, uint16_t id);
Lista<Aluno> filtrarAlunosNaoAprovadosPrimeiraOpcao(Lista<Aluno> &alunos);

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
        cursos.adicionar(new Curso(i, nomeCurso, quantidadeVagas));
    }
    for (uint16_t i = 0; i < m; i++) {
        std::string nomeAluno;
        std::cin.ignore();
        std::getline(std::cin, nomeAluno);
        double nota;
        uint16_t idCursoPrimeiraOpcao, idCursoSegundaOpcao;
        std::cin >> nota >> idCursoPrimeiraOpcao >> idCursoSegundaOpcao;
        alunos.adicionar(new Aluno(i, nomeAluno, nota, idCursoPrimeiraOpcao, idCursoSegundaOpcao));
    }
}

void processar(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    alunos.ordenar();

    auto nodeAluno = alunos.getPrimeiro();

    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        auto cursoPrimeiraOpcao = obterCursoPorId(cursos, aluno->getCodigoPrimeiraOpcao());
        cursoPrimeiraOpcao->adicionarAlunoListaIntermediaria(aluno);
        nodeAluno = nodeAluno->getProximo();
    }

    auto nodeCurso = cursos.getPrimeiro();

    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        curso->processarListaIntermediaria();
        nodeCurso = nodeCurso->getProximo();
    }

    Lista<Aluno> alunosNaoAprovados = filtrarAlunosNaoAprovadosPrimeiraOpcao(alunos);

    nodeAluno = alunosNaoAprovados.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        auto cursoSegundaOpcao = obterCursoPorId(cursos, aluno->getCodigoSegundaOpcao());
        cursoSegundaOpcao->adicionarAlunoListaIntermediaria(aluno);
        nodeAluno = nodeAluno->getProximo();
    }

    nodeCurso = cursos.getPrimeiro();
    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        curso->processarListaIntermediaria();
        nodeCurso = nodeCurso->getProximo();
    }

    nodeAluno = alunos.getPrimeiro(); // TODO: filtrarAlunosNaoAprovadosPrimeiraOpcao

    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (!aluno->isAprovadoPrimeiraOpcao()) {
            auto cursoPrimeiraOpcao = obterCursoPorId(cursos, aluno->getCodigoPrimeiraOpcao());
            cursoPrimeiraOpcao->adicionarAlunoListaEspera(aluno);
            if (!aluno->isAprovadoSegundaOpcao()) {
                auto cursoSegundaOpcao = obterCursoPorId(cursos, aluno->getCodigoSegundaOpcao());
                cursoSegundaOpcao->adicionarAlunoListaEspera(aluno);
            }
        }
        nodeAluno = nodeAluno->getProximo();
    }

    nodeCurso = cursos.getPrimeiro();
    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        curso->consolidarListaAprovados();
        nodeCurso = nodeCurso->getProximo();
    }


}

Lista<Aluno> filtrarAlunosNaoAprovadosPrimeiraOpcao(Lista<Aluno> &alunos) {
    auto alunosNaoAprovadosPrimeiraOpcao = Lista<Aluno>();

    Node<Aluno> * nodeAluno;
    nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (!aluno->isAprovadoPrimeiraOpcao()) {
            alunosNaoAprovadosPrimeiraOpcao.adicionar(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
    return alunosNaoAprovadosPrimeiraOpcao;
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
        std::cout << *noCurso->getValor() << std::endl;
        noCurso = noCurso->getProximo();
    }
}
