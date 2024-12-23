#version 330 core
out vec4 FragColor;

in vec4 fragPos;

void main() {
	int shouldDiscard = 0;
	const float low = 0.005f;
	const float high = 0.995f;

	if(low < fragPos.x && fragPos.x < high) shouldDiscard++;
	if(low < fragPos.y && fragPos.y < high) shouldDiscard++;
	if(low < fragPos.z && fragPos.z < high) shouldDiscard++;

	if(shouldDiscard > 1)
		discard;

	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}