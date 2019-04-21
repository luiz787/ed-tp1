#include <iostream>
#include "Curso.hpp"
#include "ListaException.hpp"


void read(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void process(Lista<Curso> &cursos, Lista<Aluno> &alunos);
void resolverDesempates(Lista<Curso> &cursos);
void imprimirResultado(Lista<Curso> &cursos);

Curso* obterCursoPorId(Lista<Curso> &cursos, uint16_t id);

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
    //std::cout << "Was able to read." << std::endl;
    //std::cout << "Starting to process input..." << std::endl;
}

void process(Lista<Curso> &cursos, Lista<Aluno> &alunos) {
    //std::cout << "Processing." << std::endl;

    //std::cout << "Amount of courses: " << cursos.getTamanho() << std::endl;
    //std::cout << "Amount of students: " << alunos.getTamanho() << std::endl;
    alunos.ordenar();
    //std::cout << "Ordered alunos." << std::endl;
    //alunos.imprimir();
    auto aluno = alunos.getPrimeiro();
    while (aluno != nullptr) {
        auto cursoPrimeiraOpcao = obterCursoPorId(cursos, aluno->getValor()->getCodigoPrimeiraOpcao());
        auto cursoSegundaOpcao = obterCursoPorId(cursos, aluno->getValor()->getCodigoSegundaOpcao());
        if (cursoPrimeiraOpcao->getQuantidadeVagasRemanescentes() == 0
            && cursoSegundaOpcao->getQuantidadeVagasRemanescentes() == 0) {
            cursoPrimeiraOpcao->adicionarAlunoListaEspera(aluno->getValor());
            cursoSegundaOpcao->adicionarAlunoListaEspera(aluno->getValor());
        }

        if (cursoPrimeiraOpcao->getQuantidadeVagasRemanescentes() > 0) {
            cursoPrimeiraOpcao->adicionarAlunoListaAprovados(aluno->getValor());
        } else if (cursoSegundaOpcao->getQuantidadeVagasRemanescentes() > 0) {
            cursoSegundaOpcao->adicionarAlunoListaAprovados(aluno->getValor());
            cursoPrimeiraOpcao->adicionarAlunoListaEspera(aluno->getValor());
        }

        aluno = aluno->getProximo();
    }

    resolverDesempates(cursos);
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

void resolverDesempates(Lista<Curso> &cursos) {
    //std::cout << "Resolvendo desempates." << std::endl << std::endl << std::endl;
}

void imprimirResultado(Lista<Curso> &cursos) {
    auto noCurso = cursos.getPrimeiro();
    while(noCurso != nullptr) {
        std::cout << *noCurso->getValor() << std::endl;
        noCurso = noCurso->getProximo();
    }
}
