#include <iostream>
#include "Curso.hpp"
#include "ListaException.hpp"


void read(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void process(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void imprimirResultado(Lista<Curso> &cursos);
Lista<Aluno> filtrarAlunosNaoAprovados(Lista<Aluno> &alunos);

int main() {
    try {
        Lista<Curso> cursos;
        Lista<Aluno> alunos;
        read(cursos, alunos);
        process(cursos, alunos);
        imprimirResultado(cursos);
    } catch (ListaException& e) {
        std::cout << e.what();
    }

    return 0;
}

void read(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
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

void process(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    alunos.ordenar();
    auto nodeCurso = cursos.getPrimeiro();

    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        auto nodeAluno = alunos.getPrimeiro();
        while (nodeAluno != nullptr) {
            auto aluno = nodeAluno->getValor();
            if (aluno->getCodigoPrimeiraOpcao() == curso->getId() && curso->possuiVagas()) {
                curso->adicionarAlunoListaAprovados(aluno);
                aluno->setAprovado(true);
            }
            nodeAluno = nodeAluno->getProximo();
        }
        nodeCurso = nodeCurso->getProximo();
    }

    Lista<Aluno> alunosNaoAprovados = filtrarAlunosNaoAprovados(alunos);

    nodeCurso = cursos.getPrimeiro();

    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        auto nodeAluno = alunosNaoAprovados.getPrimeiro();
        while (nodeAluno != nullptr) {
            auto aluno = nodeAluno->getValor();
            if (aluno->getCodigoSegundaOpcao() == curso->getId()
                && *aluno > *curso->getAprovados().getUltimo()->getValor()) {
                    curso->adicionarAlunoListaAprovados(aluno);
                    aluno->setAprovado(true);
            }
            if (aluno->getCodigoPrimeiraOpcao() == curso->getId()) {
                curso->adicionarAlunoListaEspera(aluno);
            }
            nodeAluno = nodeAluno->getProximo();
        }
        nodeCurso = nodeCurso->getProximo();
    }

    alunosNaoAprovados = filtrarAlunosNaoAprovados(alunos);

    nodeCurso = cursos.getPrimeiro();

    while (nodeCurso != nullptr) {
        auto curso = nodeCurso->getValor();
        auto nodeAluno = alunosNaoAprovados.getPrimeiro();
        while (nodeAluno != nullptr) {
            auto aluno = nodeAluno->getValor();
            if (aluno->getCodigoSegundaOpcao() == curso->getId()) {
                curso->adicionarAlunoListaEspera(aluno);
            }
            nodeAluno = nodeAluno->getProximo();
        }
        nodeCurso = nodeCurso->getProximo();
    }
}

Lista<Aluno> filtrarAlunosNaoAprovados(Lista<Aluno> &alunos) {
    auto alunosNaoAprovados = Lista<Aluno>();

    Node<Aluno> * nodeAluno;
    nodeAluno = alunos.getPrimeiro();
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        if (!aluno->isAprovado()) {
            alunosNaoAprovados.adicionar(aluno);
        }
        nodeAluno = nodeAluno->getProximo();
    }
    return alunosNaoAprovados;
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
