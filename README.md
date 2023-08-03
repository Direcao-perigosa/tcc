### https://www.youtube.com/watch?v=vieoHqt7pxo
### 1. Write App
### 2. Setup Google Cloud
### 3. Install and init Google Cloud SDK
### 4. Dockerflie, requirements.txt, .dockerignore
### 5. Cloud build & deploy

gcloud builds submit --tag gcr.io/direcao-ofensiva/predict_data
gcloud run deploy --image gcr.io/direcao-ofensiva/predict_data --platform managed
