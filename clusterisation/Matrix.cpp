#include "Matrix.h"

aca::Matrix::Matrix(DistClasterFunc *distance) {
    if (distance == nullptr)
        throw std::runtime_error("Empty function for counting distances between clusters");
    this->distance = distance;
}

size_t aca::Matrix::size() const
{
    return clasters.size();
}

const std::vector<aca::Claster>& aca::Matrix::getClasters() const {
    return clasters;
}

void aca::Matrix::addEntity(const Claster& ent) {
    matrix.push_back(std::vector<double>());
    std::vector<double>& newLine = matrix[matrix.size() - 1];

    for (Claster& el : clasters)
        newLine.push_back(distance->distance(el, ent));

    newLine.push_back(0);
    clasters.push_back(ent);

    for (int i = 0; i < clasters.size() - 1; i++)
        matrix[i].push_back(newLine[i]);

}

void aca::Matrix::rebuild(size_t x) {
    if (x >= clasters.size()) {
        std::cerr << "i is bigger than count of clasters ";
        throw std::runtime_error("i is bigger than count of clasters ");
    }
    for (int i = 0; i < clasters.size(); i++) {
        if (x != i)
            matrix[i][x] = matrix[x][i] = distance->distance(clasters[x], clasters[i]);
    }
}

const std::vector<double>& aca::Matrix::operator[](size_t i) const
{
    return matrix[i];
}

void aca::Matrix::unite(size_t i, size_t j) {
    if (i >= clasters.size() || j >= clasters.size() || i == j) {
        std::cerr << "i or j is bigger than count of clasters ";
        throw std::runtime_error("i or j is bigger than count of clasters ");
    }

    if (!(i < j))
        std::swap(i, j);

    clasters[i].unite(std::move(clasters[j]));

    clasters.erase(clasters.begin() + j);
    matrix.erase(matrix.begin() + j);
    for (auto& arr : matrix)
        arr.erase(arr.begin() + j);

    rebuild(i);
}

std::ostream& operator<<(std::ostream& out, const aca::Matrix& arr) {
    {
        int i = 1;
        for (const auto& claster : arr.getClasters()) {
            out << "claster " << claster.getId() << ":\n";
            for (const auto& ent : claster)
                out << "   " << ent << '\n';
        }
    }
    out << "---------------------------------------------\n";
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            printf("%.1lf\t", arr[i][j]);
        }
        out << '|' << std::endl;
    }
    out << "---------------------------------------------\n\n";
    return out;

}