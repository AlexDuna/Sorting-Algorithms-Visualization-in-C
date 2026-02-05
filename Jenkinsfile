pipeline{
  agent any

  stages{
    stage('Checkout'){
      steps{
        checkout scm
      }
    }

    stage('Build Docker Image'){
      steps{
        sh 'docker build -t sorting-visualizer-ci .'
      }
    }

    stage('Run tests in Docker'){
      steps{
        sh 'docker run --rm sorting-visualizer-ci'
      }
    }
  }

  post{
    success{
      echo 'All tests PASSED in CI.'
    }
    failure{
      echo 'Some tests FAILED in CI.'
    }
  }
}
